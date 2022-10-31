# include <cstdint>
# include <ostream>
# include <stdexcept>
# include <vector>
# include <string>
# include <map>
# include <libnet.h>
# include <stdint.h>
# include <libnet/libnet-functions.h>
# include <pcap/pcap.h>
# include <sys/types.h>

# define set_byte(value,byte_value,byte_pos) (value  | (byte_value << (2 << byte_pos)))
# define get_byte(value,byte_pos) ((uint8_t)(value & (0xFF << ( 2 << byte_pos))))


template <typename T>
struct pointer{
    T* ptr = nullptr;
};

template <typename T>
struct dpointer{
    T** ptr = nullptr;
};

struct pkt_handler {
    virtual void handler(dpointer<u_char>& dptr);
};

namespace Error
{
    const std::string ERROR_COLOR   = "\033[91m";
    const std::string SUCCESS_COLOR = "\033[92m";
    const std::string WARNING_COLOR = "\033[93m";
    const std::string RESET_COLOR   = "\033[0m";

    void write_error(const std::string& _msg);
    void die_with_error(const std::string& _msg,int code);
    void write_console(const std::string& _msg);
    void writeln(const std::string& _msg);
    void writef(const char* fmt,...);
} // namespace Error


namespace Pcap
{
    // Get interface
    bool get_ifaces(pointer<pcap_if_t>& alldevs);
    bool list_ifaces(std::map<std::string,pcap_if_t*>& ifaces);
    bool dump_to_file(pointer<char>& dev,const std::string& str,uint64_t duration);
}

namespace ip {

    enum version {
        v4 = 0x04,
        v6 = 0x06
    };



    class IP {

        private:
            bool isValid();
            //uint32_t ip_str2int(const std::string &ip);
            std::string ip_int2str(uint32_t ip);
            version v;
            std::string str_netmask;
            std::string str_ip;
            uint32_t mask = 0;
            uint32_t ip_addr;

        public:

            IP(const std::string& addr,version v = v4)
            {

                this->v =  v;
                this->str_ip = addr;

            }

            void set_netmask(int mask_bit_size);
            void set_netmask(const std::string& mask);
            IP&  get_net_prefix();
            IP&  get_broadcast_addr();
            uint32_t ip_str2int(const std::string &ip);
            friend std::ostream& operator>>(std::ostream &oss,const IP &ip);
    };
}


namespace libnet {
    struct tcp_pkt{
        uint16_t src_port;
        uint16_t dst_port;
        uint32_t seq_num;
        uint32_t ack_num; /* TCP acknowledgement number */
        uint16_t ctrl; /* TCP flags */ 
        uint16_t win_size;
        uint16_t sum;
        uint16_t urg_num;
        uint16_t length;
        uint32_t payload_s;
        uint8_t *payload;
    };
}
