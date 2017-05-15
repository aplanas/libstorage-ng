/*
 * Copyright (c) 2017 SUSE LLC
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact SUSE LLC.
 *
 * To contact SUSE LLC about this file by physical or electronic mail, you may
 * find current contact information at www.suse.com.
 */


#include <iostream>
#include <algorithm>

#include "storage/CompoundAction/CompoundActionGenerator.h"
#include "storage/CompoundAction/CompoundActionImpl.h"


namespace storage
{

    using namespace std;

    using const_iterator = vector<CompoundAction*>::const_iterator;


    CompoundActionGenerator::CompoundActionGenerator(const Actiongraph* actiongraph)
    : actiongraph(actiongraph) {}


    CompoundActionGenerator::~CompoundActionGenerator() {}


    vector<CompoundAction*>
    CompoundActionGenerator::generate() const
    {
	vector<CompoundAction*> compound_actions;

	for(auto& commit_action : actiongraph->get_commit_actions())
	{
	    auto target = CompoundAction::Impl::get_target_device(actiongraph, commit_action);
	    
	    auto compound_action = find_by_target_device(compound_actions, target);

	    if (compound_action == compound_actions.end())
		compound_actions.push_back(new CompoundAction(actiongraph, commit_action));
	    else
		(*compound_action)->add_commit_action(commit_action);
	}
	
	return compound_actions;
    }

    
    const_iterator
    CompoundActionGenerator::find_by_target_device(const vector<CompoundAction*>& compound_actions, const Device* device)
    {
	auto begin = compound_actions.begin();
	auto end = compound_actions.end();

	auto it = find_if(begin, end, 
		[device](CompoundAction* a) -> bool 
		{
		    return a->get_target_device() == device;
		});

	return it;
    }

}

