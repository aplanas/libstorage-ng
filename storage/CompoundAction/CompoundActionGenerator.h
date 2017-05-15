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


#ifndef STORAGE_COMPOUND_ACTION_GENERATOR_H
#define STORAGE_COMPOUND_ACTION_GENERATOR_H


#include <iterator>
#include <vector>


namespace storage
{

    using std::vector;

    class Actiongraph;
    class CompoundAction;
    class Device;

    class CompoundActionGenerator
    {

    public:

	using const_iterator = vector<CompoundAction*>::const_iterator;

	CompoundActionGenerator(const Actiongraph* actiongraph);
	~CompoundActionGenerator();

	vector<CompoundAction*> generate() const;

    private:

	static const_iterator find_by_target_device(const vector<CompoundAction*>& compound_actions, const Device* device);

    private:

	const Actiongraph* actiongraph;
    
    };

}

#endif
