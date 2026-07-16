% constrain
v_limit = 1; % p.u.
a_limit = 0.5; % p.u.
aa_limit = 1; % p.u.
pos_deadband = 1e-4;

% time scale
t_limit = 20;

t = 0:0.001:t_limit;
delta_t = 0.001;
fs = 1 / delta_t;

% initial state, current state
cur_pos = 5;
cur_vel = -2;
cur_acc = 0;

% debug record
target_acceleration_record = zeros(length(t),3);
target_velocity_record = zeros(length(t),3);
target_position_record = zeros(length(t),3);
profile_traj = zeros(length(t),1);

% user traj plan
for i = 1:length(t)
    if(t(i) < 10)
        profile_traj(i) = 3;
    else
        profile_traj(i) = -3;
    end
end

% profile_traj = -3*ones(length(t),1);


%% traj plan I: trapezoid
target_acceleration = cur_acc;
target_velocity = cur_vel;
target_position = cur_pos;

for i = 1:length(t)
    profile_pos = profile_traj(i);

    % step I: calculate brake distance
    brake_distance = target_velocity * target_velocity / (a_limit * 2);

    % step II: judge if velocity direction is correct
    dir_judge = (profile_pos - target_position) * target_velocity;

    % step III: judge running direction
    direction = sign(profile_pos - target_position);

    % position loop dead band
    if(abs(profile_pos - target_position) > pos_deadband)
        if(dir_judge > 0)

            % step IV: judge if current distance is within braking distance
            if( ((direction == -1) && (profile_pos - target_position >= direction*brake_distance))...
                    || ((direction == 1) && (profile_pos - target_position <= brake_distance)) )

                % step V: within the braking distance, slow down
                target_acceleration = - direction * a_limit;
            else
                % step VI: out of braking distance
                target_acceleration = direction * a_limit;
            end
            %         end
        else
            % step VII: wrong running dirction
            target_acceleration = direction * a_limit;
        end
    
        % step VIII: integral and get velocity and position
        target_velocity = target_velocity + target_acceleration * delta_t;
        % target_velocity = saturation(target_velocity, -v_limit,v_limit);
        if(target_velocity >= v_limit)
            target_acceleration = 0;
            target_velocity = v_limit;
        elseif (target_velocity <= -v_limit)
            target_acceleration = 0;
            target_velocity = -v_limit;
        end

    else
        % The position feedforward has been in deadband
        target_acceleration = 0;
        target_velocity = 0;
    end

    % step IX: integral and get position
    target_position = target_position + target_velocity * delta_t;
    
    % record the result for debug
    target_acceleration_record(i,1) = target_acceleration;
    target_velocity_record(i,1) = target_velocity;
    target_position_record(i,1) = target_position;

end

figure

subplot(3,1,1)
plot(t,target_acceleration_record(:,1));
subplot(3,1,2)
plot(t,target_velocity_record(:,1));
subplot(3,1,3)
plot(t,target_position_record(:,1));
hold on
plot(t,profile_traj);


%% traj plan II: S-curve

target_acceleration = cur_acc;
target_velocity = cur_vel;
target_position = cur_pos;

for i = 1:length(t)
    profile_pos = profile_traj(i);

    % step I: calculate brake distance
    %brake_distance = target_velocity * target_velocity / (a_limit * 2) *1.5 ;
    k3 = aa_limit / 6;
    k2 = target_acceleration / 2;
    k1 = target_velocity;
    k0 = target_position;

    brk_roots = roots([k3,k2,k1,k0]);
    brake_distance = brk_roots(1);

    % step II: judge if velocity direction is correct
    dir_judge = (profile_pos - target_position) * target_velocity;

    % step III: judge running direction
    direction = sign(profile_pos - target_position);

    % position loop dead band
    if(abs(profile_pos - target_position) > pos_deadband)
        if(dir_judge > 0)

            % step IV: judge if current distance is within braking distance
            if( ((direction == -1) && (profile_pos - target_position >= direction*brake_distance))...
                    || ((direction == 1) && (profile_pos - target_position <= brake_distance)) )

                % step V: within the braking distance, slow down
                target_acceleration = target_acceleration - direction * aa_limit * delta_t;
            else
                % step VI: out of braking distance
                target_acceleration = target_acceleration + direction * aa_limit * delta_t;
            end
        else
            % step VII: wrong running dirction
            target_acceleration = target_acceleration + direction * a_limit * delta_t;
        end

        % target_acceleration = saturation(target_acceleration, -a_limit,a_limit);
         if(target_acceleration >= a_limit)
             target_acceleration = a_limit;
         elseif (target_acceleration <= -a_limit)
             target_acceleration = -a_limit;
         end
    
        % step VIII: integral and get velocity and position
        target_velocity = target_velocity + target_acceleration * delta_t;
        % target_velocity = saturation(target_velocity, -v_limit,v_limit);
        if(target_velocity >= v_limit)
             target_acceleration = 0;
            target_velocity = v_limit;
        elseif (target_velocity <= -v_limit)
             target_acceleration = 0;
            target_velocity = -v_limit;
        end

    else
        % The position feedforward has been in deadband
        target_acceleration = 0;
        target_velocity = 0;
    end

    % step IX: integral and get position
    target_position = target_position + target_velocity * delta_t;
    
    % record the result for debug
    target_acceleration_record(i,2) = target_acceleration;
    target_velocity_record(i,2) = target_velocity;
    target_position_record(i,2) = target_position;

end

figure

subplot(3,1,1)
plot(t,target_acceleration_record(:,2));
subplot(3,1,2)
plot(t,target_velocity_record(:,2));
subplot(3,1,3)
plot(t,target_position_record(:,2));
hold on
plot(t,profile_traj);




%% traj plan III: filter-curve

% s domain
s = tf('s');

% 2rd-order filter
% omega_spd = 50*2*pi;
omega_spd = aa_limit * exp(1) / v_limit*10;
xi = 1;
q = 1/2/xi;
spd_filter = omega_spd^2 / (s^2 + 2*xi*omega_spd*s + omega_spd^2);

% fiugre;
% bode(spd_filter);
% figure
% step(spd_filter);

f0 = omega_spd*2*q;
theta = f0 / 2/ pi/ fs;
sin_theta = sin(theta);
cos_theta = cos(theta);
alpha = sin_theta / 2 / q;

gain = 1;

a0 = 1+alpha;
a1 = -2*cos_theta/a0;
a2 = (1 - alpha)/a0;
b0 = gain * (1 - cos_theta) / (2*a0);
b1 = gain * (1 - cos_theta) / a0;
b2 = gain * (1 - cos_theta) / (2*a0);

% IIR filter parameter
x1 = 0;
x2 = 0;
y1 = 0;
y2 = 0;



target_acceleration = cur_acc;
target_velocity = cur_vel;
target_position = cur_pos;

for i = 1:length(t)
    profile_pos = profile_traj(i);

    % step I: calculate brake distance
    brake_distance = (target_acceleration + 2*target_velocity*omega_spd)/omega_spd^2;

    % step II: judge if velocity direction is correct
    dir_judge = (profile_pos - target_position) * target_velocity;

    % step III: judge running direction
    direction = sign(profile_pos - target_position);

    % position loop dead band
    if(abs(profile_pos - target_position) > pos_deadband)
        if(dir_judge > 0)

            % step IV: judge if current distance is within braking distance
            if( ((direction == -1) && (profile_pos - target_position >= direction*brake_distance))...
                    || ((direction == 1) && (profile_pos - target_position <= brake_distance)) )

                % step V: within the braking distance, slow down
                speed_ref = 0;

            else
                % step VI: out of braking distance
                speed_ref = direction * v_limit;
            end
        else
            % step VII: wrong running dirction
            speed_ref = direction * v_limit;
        end


    
        % step VIII: integral and get velocity and position
%         target_velocity = target_velocity + target_acceleration * delta_t;
        % target_velocity = saturation(target_velocity, -v_limit,v_limit);
        
        target_velocity_new = b0 * speed_ref + b1 * x1 + b2 * x2  ...
            - a1 * y1 - a2 * y2;

        x2 = x1;
        x1 = speed_ref;
        y2 = y1;
        y1 = target_velocity_new;

        % target_acceleration = saturation(target_acceleration, -a_limit,a_limit);
        target_acceleration = (target_velocity_new - target_velocity)/delta_t;

        if(target_acceleration >= a_limit)
             target_acceleration = a_limit;
         elseif (target_acceleration <= -a_limit)
             target_acceleration = -a_limit;
         end
       
        target_velocity = target_velocity + target_acceleration * delta_t;
        y1 = target_velocity;


        if(target_velocity >= v_limit)
%            target_acceleration = 0;
            target_velocity = v_limit;
        elseif (target_velocity <= -v_limit)
%            target_acceleration = 0;
            target_velocity = -v_limit;
        end

    else
        % The position feedforward has been in deadband
%         target_acceleration = 0;
%         target_velocity = 0;
    end

    % step IX: integral and get position
    target_position = target_position + target_velocity * delta_t;
    
    % record the result for debug
    target_acceleration_record(i,3) = target_acceleration;
    target_velocity_record(i,3) = target_velocity;
    target_position_record(i,3) = target_position;

end

figure

subplot(3,1,1)
plot(t,target_acceleration_record(:,3));
ylim([-1.5,1.5]);
subplot(3,1,2)
plot(t,target_velocity_record(:,3));
subplot(3,1,3)
plot(t,target_position_record(:,3));
hold on
plot(t,profile_traj);



