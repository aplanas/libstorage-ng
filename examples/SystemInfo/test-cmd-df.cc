
#include <iostream>

#include <storage/SystemInfo/SystemInfoImpl.h>

using namespace std;
using namespace storage;


void
test_df(SystemInfo::Impl& system_info, const string& path)
{
    try
    {
	const CmdDf& cmd_df = system_info.getCmdDf(path);
	cout << "CmdDf success for '" << path << "'" << endl;
	cout << cmd_df << endl;
    }
    catch (const exception& e)
    {
	cerr << "CmdDf failed for '" << path << "'" << endl;
    }
}


int
main()
{
    set_logger(get_logfile_logger());

    SystemInfo::Impl system_info;

    test_df(system_info, "/home/arvin");
}
