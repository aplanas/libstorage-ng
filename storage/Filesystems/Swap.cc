/*
 * Copyright (c) [2014-2015] Novell, Inc.
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
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#include "storage/Filesystems/SwapImpl.h"
#include "storage/Devicegraph.h"


namespace storage
{

    using namespace std;


    Swap*
    Swap::create(Devicegraph* devicegraph)
    {
	Swap* ret = new Swap(new Swap::Impl());
	ret->Device::create(devicegraph);
	return ret;
    }


    Swap*
    Swap::load(Devicegraph* devicegraph, const xmlNode* node)
    {
	Swap* ret = new Swap(new Swap::Impl(node));
	ret->Device::load(devicegraph);
	return ret;
    }


    Swap::Swap(Impl* impl)
	: BlkFilesystem(impl)
    {
    }


    Swap*
    Swap::clone() const
    {
	return new Swap(get_impl().clone());
    }


    Swap::Impl&
    Swap::get_impl()
    {
	return dynamic_cast<Impl&>(Device::get_impl());
    }


    const Swap::Impl&
    Swap::get_impl() const
    {
	return dynamic_cast<const Impl&>(Device::get_impl());
    }


    vector<Swap*>
    Swap::get_all(Devicegraph* devicegraph)
    {
	return devicegraph->get_impl().get_devices_of_type<Swap>();
    }


    vector<const Swap*>
    Swap::get_all(const Devicegraph* devicegraph)
    {
	return devicegraph->get_impl().get_devices_of_type<const Swap>();
    }


    bool
    is_swap(const Device* device)
    {
	return is_device_of_type<const Swap>(device);
    }


    Swap*
    to_swap(Device* device)
    {
	return to_device_of_type<Swap>(device);
    }


    const Swap*
    to_swap(const Device* device)
    {
	return to_device_of_type<const Swap>(device);
    }

}
