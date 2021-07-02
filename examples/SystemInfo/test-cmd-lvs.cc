
#include <iostream>

#include <storage/SystemInfo/SystemInfoImpl.h>

using namespace std;
using namespace storage;


void
test_lvs(SystemInfo::Impl& system_info)
{
    try
    {
	const CmdLvs& cmd_lvs = system_info.getCmdLvs();
	cout << "CmdLvs success" << endl;
	cout << cmd_lvs << endl;
    }
    catch (const exception& e)
    {
	cerr << "CmdLvs failed" << endl;
    }
}


int
main()
{
    set_logger(get_logfile_logger());

    SystemInfo::Impl system_info;

    test_lvs(system_info);
}
