/**
 * @file workflow.cpp
 * @author Javnson (javnson@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2024-09-30
 * 
 * @copyright Copyright GMP(c) 2024
 * 
 */

// gmp header
#include <gmp_core.hpp>

#include <core/pm/workflow/workflow.hpp>

gmp_wf_node_base_gt wf_end_node_entity(gmp_workflow_t::gmp_wf_end_id);
gmp_wf_node_base_gt* wf_end_node = &wf_end_node_entity;


size_gt gmp_workflow_t::get_curr_node_id()
{
	// BUG 
	if (last_node == nullptr)
		return gmp_workflow_t::gmp_wf_end_id;
	return curr_node->get_id();
}

size_gt gmp_workflow_t::get_last_node_id()
{
	if (last_node == nullptr)
		return gmp_workflow_t::gmp_wf_end_id;
	return last_node->get_id();
}

ec_gt gmp_workflow_t::process()
{
	// check the parameters
//        assert(curr_node);

		// check if the class is running
	if (flag_enable)
	{
		if (curr_node == wf_end_node) // reach the stop node
		{
			// clear the enable flag
			flag_enable = 0;

#if defined SPECIFY_WORKFLOW_START_END_CALLBACK
			// The tail function would be called
			if (tail_callback)
				tail_callback(this);
#endif // SPECIFY_WORKFLOW_START_END_CALLBACK
		}

		// call the node routine and get the next node
		gmp_wf_node_base_gt* next_node = curr_node->node_routine(this);

		// keep the same position
//         if (next_node == nullptr || next_node == curr_node)
//         {
//             return GMP_STAT_OK;
//         }

		// in this case the process permit user using loop to itself.
		// WARNING
		if (next_node == nullptr)
		{
			return GMP_STAT_OK;
		}

		// consider the prior node
		if (next_node == prior_node)
		{
			flag_usr_modify = 0;
			return switch_to(prior_node);
		}

		// bug judge if transfer to user
		else
		{
			// switch to next node
			return switch_to(next_node);
		}
	}

	// do nothing
	return GMP_STAT_OK;
}

ec_gt gmp_workflow_t::switch_to(gmp_wf_node_base_gt *node)
{
#ifdef SPECIFY_WORKFLOW_CHECK_REACHABLE
	if (!flag_verify_disabled
		&& (verify_fn != nullptr)
		&& (node != wf_end_node)) // bypass the end point.
	{
		if (!verify_fn(curr_node, node))
			return GMP_STAT_WF_NONREACHABLE;
	}
#endif // SPECIFY_WORKFLOW_CHECK_REACHABLE

#if defined SPECIFY_WORKFLOW_NODE_OWN_LEAVE
	// decide to leave this node
	curr_node->node_leave(this);
#endif // SPECIFY_WORKFLOW_NODE_OWN_LEAVE

	// state transfer
	last_node = curr_node;
	curr_node = node;
	last_switch_time = switch_time;

#if defined SPECIFY_WORKFLOW_MULTITIMER_TICK
	if (get_timer_tick)
		switch_time = get_timer_tick();
	else
#endif // SPECIFY_WORKFLOW_MULTITIMER_TICK

		switch_time = wf_get_tick();

	// call the transfer welcome function 
	gmp_wf_node_base_gt* current_trnas_node
		= curr_node->node_transfer(this);

	// if emergency situation happened, 
	// We should switch to the emergency situation.
	if ((current_trnas_node != nullptr))
		return switch_to(current_trnas_node);

	return GMP_STAT_OK;
}

