/** \file gti_step_past_bp_events.h
 * 
 *  This header defines the interface used by driver to issue a callback to debugger
 *  when it is about to step (over a breakpoint) and finishes step during run.
 *  The callback is to allow cross triggers to be disabled before the step and 
 *  reenabled after the step.
 * 
 *  Copyright (c) 2012-2015, Texas Instruments Inc., All rights reserved.
 */

#ifndef GTI_STEP_PAST_BP_EVENTS_H
#define GTI_STEP_PAST_BP_EVENTS_H

// This is an interface that a GTI driver can use to notify other components in
// the system that it's about to step past a breakpoint prior to a run.  
// Clients can listen to this event and respond to it if needed.  For instance, 
// such a step will generate a halt which could have implications on other 
// cores in the system if cross triggering of some form is enabled.  Clients 
// that setup cross triggering can use this event to temporarily disable cross
// triggering.

typedef const char* ( *StepPastBpEventFn )( void* pContext );

typedef struct StepPastBpEvents_
{
	// Called to notify clients before the target is stepped past a breakpoint.
	//
	// If a non-null, non-empty error is returned, the caller should not 
	// attempt to step past the breakpoint and should abort with the error 
	// indicated.  FinishedSteppingPast does not need to be calledin that case.
	
	StepPastBpEventFn aboutToStepPast;
	
	// Called to notify clients after the target has been stepped past the 
	// breakpoint and is halted.
	// 
	// If a non-null, non-empty error is returned, the caller abort with the 
	// error indicated.
	
	StepPastBpEventFn finishedSteppingPast;
	
	// Client context to be  passed to both event functions.
	
	void* pContext;
} StepPastBpEvents;

#endif // GTI_STEP_PAST_BP_EVENTS_H
