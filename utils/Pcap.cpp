# define HAVE_REMOTE

# include <cstddef>
# include <vector>
# include <signal.h>
# include <cstdint>
# include <pcap.h>
# include <cstring>
# include <string>
# include <map>
# include <pcap/pcap.h>
# include "./Utils.hpp"

bool Pcap::get_ifaces(pointer<pcap_if_t> &alldevs)
{
    char errbuf[PCAP_ERRBUF_SIZE] = {0};
    if(pcap_findalldevs(&alldevs.ptr, errbuf) == -1)
    {
        Error::write_error(std::string(errbuf));
        return false;
    }
    return true;
}

bool Pcap::dump_to_file(pointer<char> &dev, const std::string &filename, uint64_t duration)
{
    pcap_t* capture = nullptr;
    pcap_dumper_t* dumpfile = nullptr;
    pcap_pkthdr* header = nullptr;
    u_char* pkt_data = nullptr;
    int res = -1;
    
    capture = pcap_open_live(dev.ptr, 65536, PCAP_OPENFLAG_PROMISCUOUS,2500,NULL);
    if(capture == NULL)
        return false;
    
    dumpfile = pcap_dump_open(capture,filename.c_str());
    if(dumpfile == nullptr)
        return false;

    // while((res = pcap_next_ex(capture,&header,(const u_char**)&pkt_data)) > 0)
    // {

    // } 

    return true;
}

bool Pcap::list_ifaces(std::map<std::string,pcap_if_t*>& ifaces)
{
    pointer<pcap_if_t> if_ptr;
    if(!get_ifaces(if_ptr))
    {
        Error::write_error("[-] Could not get interface list");
        return false;
    }

    for(pcap_if_t *iface = if_ptr.ptr; iface != NULL; iface = iface->next)
    {
        auto s = std::string(iface->name);
        ifaces[s] = iface;
    }

    return true;
}