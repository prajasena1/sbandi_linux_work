/// Color code
#define COLOR_DEFAULT               "\033[0m"
#define COLOR_BLACK                 "\033[1;30m"
#define COLOR_RED                   "\033[1;31m"
#define COLOR_GREEN                 "\033[1;32m"
#define COLOR_BROWN                 "\033[1;33m"
#define COLOR_BLUE                  "\033[1;34m"
#define COLOR_MAGENTA               "\033[1;35m"
#define COLOR_CYAN                  "\033[1;36m"
#define COLOR_LIGHTGRAY             "\033[1;37m"
#define COLOR_TEXT(color, text)     color text COLOR_DEFAULT

strout << COLOR_GREEN << std::setw(file_name_len) << std::left
    << file_name.c_str() << "\t\t100.00"
    << COLOR_DEFAULT << std::endl;

session->Print("\nMsgAssembler Files are saved into directory [" COLOR_TEXT(COLOR_CYAN, "%s") "]\n", GetDataRecvPath().c_str() );

////////////////////////////////////////////////////////////////////////////////////////
int *a[35]; declares an array of 35 pointers to ints. 

int (*a)[35]; declares a pointer to an array of 35 ints. 

////////////////////////////////////////////////////////////////////////////////////////
// Function Pointers
// A pointer that points to a function (function pointer) can be declared like this:
int (*f)(int,int);      //this is a pointer to a function taking 2 ints as arguments and returning one 
f = &pow;               //now function pow can be called using the pointer f

//Even if in C++ you have other means to avoid the using of function pointers, 
//the new operator can be used to allocate memory for a pointer to a function:
int (**f)(int,int) = new (int (*) (int,int));

////////////////////////////////////////////////////////////////////////////////////////
//Pointers to members

typedef int X::*my_pointer_to_member;               /// pointer to data member
typedef void (X::*my_pointer_to_function) (int);    /// pointer to member function

my_pointer_to_member ptiptr = &X::a;
my_pointer_to_function ptfptr = &X::f;

X xobject;
xobject.*ptiptr = 10;   /// member pointer dereference
cout << "The value of a is " << xobject.*ptiptr << endl;

(xobject.*ptfptr) (20); /// member pointer dereference

////////////////////////////////////////////////////////////////////////////////////////

#include <sstream>

std::ostringstream strout;
std::copy ( context->m_acquired_targets.begin(),
            context->m_acquired_targets.end(),
            std::ostream_iterator<uint32_t>(strout, ","));
strout.str().c_str()
strout.str("");

strout << "Details of DirServResponse "
    << "site_id = [" << pResponse->m_site_id << "] "
    << "service_name = [" << pResponse->m_service_name.c_str() << "] "
    << "service_id = [" << pResponse->m_service_id << "] "
    << "service_addr = [" << pResponse->m_service_addr.c_str() << "] "
    << "error = [" << pResponse->m_error.c_str() << "] "
    ;
CONSOLE_PRINT(8,"TargetAssetManager::OnGetNMSServiceAddrFromDirService: %s\n",
              strout.str().c_str());

////////////////////////////////////////////////////////////////////////////////////////

void getFileLength(const string & file, uint32_t &file_length)
{
    /// Test Update_ContentBlock
    std::cout << "\t Getting the content of file " << file.c_str() << std::endl;

    std::ifstream is;
    is.open (file.c_str(), std::ios::binary );

    // get file_length of file:
    is.seekg (0, std::ios::end);
    file_length = is.tellg();
    is.close();

    return;
}

////////////////////////////////////////////////////////////////////////////////////////
/// binary data into file
std::ofstream dump_file( "miq_dump_file", std::ofstream::binary );
dump_file.write( buffer, length );
dump_file.close();

/// read binary data from file
std::ifstream is;
is.open ("temp_x", std::ios::binary );

// get file_length of file:
is.seekg (0, std::ios::end);
size_t file_length = is.tellg();
is.seekg (0, std::ios::beg);

char *file_buffer = new char [file_length+1];
// read data as a block:
is.read (file_buffer,file_length);
is.close();

////////////////////////////////////////////////////////////////////////////////////////
string full_file_path;
std::ofstream ofstr ;

/// open the file in append mode if user selected to save the details into file
ofstr.open (full_file_path.c_str(), std::ios::out|std::ios::app);

if ( !ofstr.is_open() )
{
    session->Print("PrintTargetDescriptors failed to open file <%s> error <%s>\n",
               full_file_path.c_str(), strerror(errno) );
    return ;
}
ofstr << std::string(100, '<') << std::endl;
ofstr << std::string(100, '-') << std::endl;
ofstr << "There are [" << m_asset_map.size() << "] Targets !\n" << std::endl;

////////////////////////////////////////////////////////////////////////////////////////
#include <iomanip>

strout << COLOR_BROWN << std::setw(file_name_len) << std::left
    << file_name.c_str() << "\t\t"
    << std::fixed << std::setprecision (2)
    << float(m_file_content_sent_map[file_name.c_str()])*100.00f/float(updManifestList[i].GetFootPrint()) 
    << COLOR_DEFAULT << std::endl;

////////////////////////////////////////////////////////////////////////////////////////
//Dynamic arrays - I
//array of pointers

Myclass **array = new Myclass*[N];
for (int i = 0; i < size1; i++)
{
    array[i] = new Myclass;
}

//To deleted the allocated memory you must go through the first array and apply delete to
//every element and then delete[] the main one:
for (int i=0;i<size1;i++)
{
    delete array[i];
}
delete[] array

////////////////////////////////////////////////////////////////////////////////////////
//Dynamic arrays - II
//In order to obtain a 2-dimensional array you can do something similar with this:

Myclass **array = new Myclass*[N];
for (int i = 0; i < size1; i++)
{
    array[i] = new Myclass[size2];
}

//To deleted the allocated memory you must go through the first array and apply delete[] to
//every element and then delete[] the main one:
for (int i=0;i<size1;i++)
{
    delete[] array[i];
}
delete[] array

////////////////////////////////////////////////////////////////////////////////////////
/// export TargetInventory to ostream
std::ostream& operator<< (std::ostream& out, const TargetInventory& r)
{
    out << "TargetInventory: \n";
    out << "\tTargetDescriptor " << (*(r.GetTargetDescriptor())) << "\n";

    out << "\tFreeSpace=[" << r.GetFreeSpace() << "]\n"
        << "\tTotalSpace=[" << r.GetTotalSpace() << "]\n"
        << "\tInvItemsOffset=[" << r.GetInvItemsOffset() << "]\n"
        << "\tTotalInvItems=[" << r.GetTotalInvItems() << "]\n";

    /// inventory items
    const std::vector<InventoryItem>& inventory_items = r.GetInventoryItem();
    std::copy( inventory_items.begin(), inventory_items.end(), std::ostream_iterator<InventoryItem>(out, "\n") );
    return out;
}

bool TargetInventory::operator ==(const TargetInventory &other) const
{
    return *m_td_ptr == *other.m_td_ptr &&
        m_freespace == other.m_freespace &&
        m_totalspace == other.m_totalspace &&
        m_vector_inventory_item == other.m_vector_inventory_item ; 
}

bool TargetInventory::operator !=(const TargetInventory &other) const
{
    return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////
///
/// Comparison less 
///
bool ManifestItem::operator <(const ManifestItem &r) const
{
    return (GetType() < r.GetType()) ||
        (GetType()==r.GetType() && GetFileName() < r.GetFileName()) ||
        (GetType()==r.GetType() && GetFileName()==r.GetFileName() && GetVersion() < r.GetVersion()) ||
        (GetType()==r.GetType() && GetFileName()==r.GetFileName() && GetVersion()==r.GetVersion() && GetHash() < r.GetHash()) ;
}

////////////////////////////////////////////////////////////////////////////////////////

bool operator < ( const UpdCmdParam & l , const InventoryItem & r )
{
    return ( l.m_hash < r.GetHash() ) ||
        ( l.m_hash == r.GetHash() && l.m_filename < r.GetFileName() ) ||
        ( l.m_hash == r.GetHash() && l.m_filename == r.GetFileName() && l.m_version < r.GetVersion() );
}

////////////////////////////////////////////////////////////////////////////////////////
typedef std::set<uint32_t>                SetTargetIDs;
SetTargetIDs set_lh, set_rh, intersect;
// populate set_lh and set_rh
std::set_intersection( set_lh.begin(), set_lh.end(), set_rh.begin(), set_rh.end(),
                       std::insert_iterator<SetTargetIDs>(intersect, intersect.begin())
                       );

/// append the intersection of targets_a & targets_b to targets_c
std::set_difference(targets_a.begin(),
                    targets_a.end(),
                    targets_b.begin(),
                    targets_b.end(),
                    std::insert_iterator<SetTargetIDs>(targets_c, targets_c.end())
                   );

////////////////////////////////////////////////////////////////////////////////////////
std::vector<int> output;
std::set<int> merged_results;

std::copy(merged_results.begin(), merged_results.end(),
     insert_iterator<std::vector<int> >(output, output.end()));

////////////////////////////////////////////////////////////////////////////////////////
//convert integer to void* for context
uint32_t element_id;
void *ctx = reinterpret_cast<void*>(element_id);
//convert back context into relevant integer value
uint32_t ctx_obj_id = *reinterpret_cast<uint32_t_alias*>(&ctx);

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
