
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE libstorage

#include <boost/algorithm/string.hpp>
#include <boost/test/unit_test.hpp>

#include "storage/Utils/HumanString.h"
#include "storage/Devices/DiskImpl.h"
#include "storage/Devices/PartitionTable.h"
#include "storage/Devices/Partition.h"
#include "storage/Devicegraph.h"
#include "storage/StorageImpl.h"
#include "storage/Environment.h"


using namespace std;
using namespace storage;


class Fixture
{
public:

    Fixture()
    {
	Storage::Impl::reset_global_sid();

	Environment environment(true, ProbeMode::NONE, TargetMode::DIRECT);

	storage = make_unique<Storage>(environment);

	Devicegraph* devicegraph = storage->get_staging();

	Disk* sda = Disk::create(devicegraph, "/dev/sda");
	sda->set_size(80 * GiB);
	sda->get_impl().set_transport(Transport::SATA);

	PartitionTable* gpt = sda->create_partition_table(PtType::GPT);

	Partition* sda1 = gpt->create_partition("/dev/sda1", Region(2048, 32768, 512), PartitionType::PRIMARY);
	sda1->set_size(1 * GiB);
	sda1->set_id(ID_LINUX);

	storage->check();
    }

    const Storage* get_storage() const { return storage.get(); }

private:

    unique_ptr<Storage> storage;

};


BOOST_FIXTURE_TEST_CASE(test_disk, Fixture)
{
    string expected = "Disk sid:42 displayname:/dev/sda name:/dev/sda region:[0, 167772160, 512 B] topology:[0 B, 0 B] range:256 transport:SATA";

    ostringstream out;
    out << *(Disk::find_by_name(get_storage()->get_staging(), "/dev/sda"));

    BOOST_CHECK_EQUAL(out.str(), expected);
}


BOOST_FIXTURE_TEST_CASE(test_partition, Fixture)
{
    string expected = "Partition sid:44 displayname:/dev/sda1 name:/dev/sda1 region:[2048, 2097152, 512 B] topology:[0 B, 0 B] type:primary id:0x83";

    ostringstream out;
    out << *(Partition::find_by_name(get_storage()->get_staging(), "/dev/sda1"));

    BOOST_CHECK_EQUAL(out.str(), expected);
}


BOOST_FIXTURE_TEST_CASE(test_devicegraph, Fixture)
{
    vector<string> expected = {
	"Disk sid:42 displayname:/dev/sda name:/dev/sda region:[0, 167772160, 512 B] topology:[0 B, 0 B] range:256 transport:SATA --> 43",
	"Gpt sid:43 displayname:gpt --> 44",
	"Partition sid:44 displayname:/dev/sda1 name:/dev/sda1 region:[2048, 2097152, 512 B] topology:[0 B, 0 B] type:primary id:0x83 -->",
	"User source-sid:42 target-sid:43",
	"Subdevice source-sid:43 target-sid:44"
    };

    ostringstream out;
    out << *(get_storage()->get_staging());

    BOOST_CHECK_EQUAL(out.str(), boost::join(expected, "\n") + "\n");
}
