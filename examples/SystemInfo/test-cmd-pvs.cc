
#include <iostream>

#include <storage/SystemInfo/SystemInfoImpl.h>

using namespace std;
using namespace storage;


void
test_pvs(SystemInfo::Impl& system_info)
{
    try
    {
	const CmdPvs& cmd_pvs = system_info.getCmdPvs();
	cout << "CmdPvs success" << endl;
	cout << cmd_pvs << endl;
    }
    catch (const exception& e)
    {
	cerr << "CmdPvs failed" << endl;
    }
}


int
main()
{
    set_logger(get_logfile_logger());

    SystemInfo::Impl system_info;

    test_pvs(system_info);
}
