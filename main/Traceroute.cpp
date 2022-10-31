# include <iostream>
# include <string>
# include <libnet.h>
# include <libnet/libnet-functions.h>
# include <libnet/libnet-structures.h>
# include <pcap/pcap.h>
# include "../utils/Utils.hpp"


bool libnet_initialize(pointer<libnet_context>& l,int inj_type,std::string iface,std::string& errbuff)
{
    char* ebuff = new char[LIBNET_ERRBUF_SIZE];
    auto ctx = libnet_init(inj_type,iface.c_str(),ebuff);
    if(ctx == nullptr)
    {
        errbuff = std::string(ebuff);
        return false;
    }
    l.ptr = ctx;
    return true;
}

void iface_menu(std::map<std::string,pcap_if_t*>& ifaces)
{
    Error::writeln("[+] Available interfaces");
    for(auto& [ k, v ] : ifaces)
    {
        Error::writeln(" [*] " + k);
    }
}

void version_string()
{
    auto s = std::string(pcap_lib_version());
    Error::writeln("[+] " + s);
}

pointer<pcap_if_t>& select_iface(std::map<std::string,pcap_if_t*>& ifaces) 
{
    std::string input;
    Error::write_console("[+] Enter iterface name of choice: ");
    std::getline(std::cin,input);
    static pointer<pcap_if_t> p;

    if(!ifaces.count(input))
    {
        p.ptr = (pcap_if_t*)-1;
        return p;
    }

    p.ptr = ifaces[input];
    return p;
}

void libnet_free(pointer<libnet_context>& l)
{
    libnet_destroy(l.ptr);
}

int main()
{

    pointer<libnet_context> l;
    bool iface_navailable = false;
    std::string errbuff;

    auto is_initialized = libnet_initialize(l,LIBNET_RAW4,"eth0",errbuff);

    if(!is_initialized)
    {
        Error::die_with_error("[-] Failed to initialized libnet\n", -1);
    }

    Error::writeln("[+] Libnet was initialized successfully");
    version_string();
    
    std::map<std::string,pcap_if_t*> ifaces;
    if(!Pcap::list_ifaces(ifaces))
    {
       Error::write_error("[-] Could not list interfaces\n");
       exit(-1);
    }

    iface_menu(ifaces);
    auto iface = select_iface(ifaces);

    if(iface.ptr == (pcap_if_t*)-1)
        Error::write_error("[-] Unrecognized interface name\n");

    auto _ip = ip::IP{"0.0.0.0"};
    Error::writef("%d\n",_ip.ip_str2int("127.0.0.1"));

    libnet_free(l);
    
    return 0;
}