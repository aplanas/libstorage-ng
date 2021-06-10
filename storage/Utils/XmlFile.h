/*
 * Copyright (c) [2010-2014] Novell, Inc.
 * Copyright (c) [2019-2021] SUSE LLC
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


#ifndef STORAGE_XML_FILE_H
#define STORAGE_XML_FILE_H


#include <libxml/tree.h>
#include <string>
#include <vector>
#include <sstream>
#include <optional>
#include <boost/noncopyable.hpp>

#include "storage/Utils/AppUtil.h"


namespace storage
{
    using namespace std;


    class XmlFile : private boost::noncopyable
    {

    public:

	XmlFile();
	XmlFile(const string& filename);

	~XmlFile();

	bool save_to_file(const string& filename) const;

	string save_to_string() const;

	void setRootElement(xmlNode* node)
	    { xmlDocSetRootElement(doc, node); }

	const xmlNode* getRootElement() const
	    { return xmlDocGetRootElement(doc); }

    private:

	xmlDoc* doc;

    };


    xmlNode* xmlNewNode(const char* name);
    xmlNode* xmlNewComment(const char* content);

    xmlNode* xmlNewChild(xmlNode* node, const char* name);


    const xmlNode* getChildNode(const xmlNode* node, const char* name);
    vector<const xmlNode*> getChildNodes(const xmlNode* node, const char* name);

    vector<const xmlNode*> getChildNodes(const xmlNode* node);


    bool getChildValue(const xmlNode* node, const char* name, string& value);
    bool getChildValue(const xmlNode* node, const char* name, bool& value);


    template<typename Type>
    bool getChildValue(const xmlNode* node, const char* name, Type& value)
    {
	static_assert(std::is_integral<Type>::value, "not integral");

	string tmp;
	if (!getChildValue(node, name, tmp))
	    return false;

	std::istringstream istr(tmp);
	classic(istr);
	istr >> value;
	return true;
    }


    template<typename Type>
    bool getChildValue(const xmlNode* node, const char* name, vector<Type>& values)
    {
	vector<const xmlNode*> children = getChildNodes(node, name);

	for (const xmlNode*& child : children)
	    values.push_back((const char*) child->content);

	return !children.empty();
    }


    void setChildValue(xmlNode* node, const char* name, const char* value);
    void setChildValue(xmlNode* node, const char* name, const string& value);
    void setChildValue(xmlNode* node, const char* name, bool value);


    template<typename Type>
    void setChildValue(xmlNode* node, const char* name, const Type& value)
    {
	static_assert(std::is_integral<Type>::value, "not integral");

	std::ostringstream ostr;
	classic(ostr);
	ostr << value;
	setChildValue(node, name, ostr.str());
    }


    template<typename Type>
    void setChildValue(xmlNode* node, const char* name, const vector<Type>& values)
    {
	for (const Type& value : values)
	    setChildValue(node, name, value);
    }


    template<typename Type>
    void setChildValueIf(xmlNode* node, const char* name, const Type& value, bool pred)
    {
	if (pred)
	    setChildValue(node, name, value);
    }


    template<typename Type>
    void setChildValue(xmlNode* node, const char* name, const std::optional<Type>& value)
    {
	if (value)
	    setChildValue(node, name, value.value());
    }

}


#endif
