
function blkStruct = slblocks

blkStruct.Name = sprintf('GMP Utility Library');
blkStruct.OpenFcn = 'disp(''Welcome to GMP Utility Library'')';

 % Library slx file name
Browser.Library = 'gmp_simulink_utilities';

% Name Displayed in Simulink Library Browser
Browser.Name = 'GMP Utilities Library';
 
blkStruct.Browser = Browser;

