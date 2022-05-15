//#include <windows.h>
#include <time.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;
#include "udp_simple/udp.hxx"
#include "net_fdm.hxx"



/* double htond (double x)	
{
    int * p = (int*)&x;
    int tmp = p[0];
    p[0] = htonl(p[1]);
    p[1] = htonl(tmp);

    return x;
}

float htonf (float x)	
{
    int * p = (int *)&x;
    *p = htonl(*p);
    return x;
}

SOCKET sendSocket = -1;
struct sockaddr_in sendAddr;

// IP and port where FG is listening
char * fg_ip = "127.0.0.1";
int fg_port = 5500;

// update period.  controls how often updates are
// sent to FG.  in seconds.
int update_period = 1000; */

void run();
    char * fg_ip = "127.0.0.1";
    uint16_t fg_port = 5500;
    int update_period = 1;
int main(int argc, char ** argv)
/* {
    WSAData wd;
    if (WSAStartup(MAKEWORD(2,0),&wd) == 0)
    {
        memset(&sendAddr,0,sizeof(sendAddr));
        sendAddr.sin_family = AF_INET;
        sendAddr.sin_port = htons(fg_port);
        sendAddr.sin_addr.S_un.S_addr = inet_addr(fg_ip);

        sendSocket = socket(AF_INET,SOCK_DGRAM,0);
        if (sendSocket != INVALID_SOCKET)
        {
            run();
        }
        else
        {
            cout << "socket() failed" << endl;
        }
    }
    else
    {
        cout << "WSAStartup() failed" << endl;
    }

    return 0;
} */

{
    run();
    return 0;
}

#define D2R (3.14159 / 180.0)

void run()
{
        //iu1LA.LAdata["H"] = 1000.0;
    //iu1LA.LAdata["lat"] = 43.4507* 0.017453292519943295769236907684886127134428718885417254560;
    //iu1LA.LAdata["lon"] = 39.9585* 0.017453292519943295769236907684886127134428718885417254560;
    double latitude = 43.4507; // degs
    double longitude = 39.9585; // degs
    double altitude = 1000.0; // meters above sea level
 
    float roll = 0.0; // degs
    float pitch = 0.0; // degs
    float yaw = 0.0; // degs

    float visibility = 5000.0; // meters

    while (true)
    {
        sleep(update_period);

        FGNetFDM fdm;
        memset(&fdm,0,sizeof(fdm));
        fdm.version = FG_NET_FDM_VERSION;

        fdm.latitude = latitude * D2R;
        fdm.longitude = longitude * D2R;
        fdm.altitude = altitude;

        fdm.phi = roll * D2R;
        fdm.theta = pitch * D2R;
        fdm.psi = yaw * D2R;

        fdm.num_engines = 1;

        fdm.num_tanks = 1;
        fdm.fuel_quantity[0] = 100.0;

        fdm.num_wheels = 3;

        fdm.cur_time = time(0);
        fdm.warp = 1;

        fdm.visibility = visibility;
        //udpSend(const char *msg,size_t len ,const char *HOSTNAME, uint16_t PORT);
        udpSend((char *)&fdm,sizeof(fdm),fg_ip,fg_port);

        static bool flag = true;
        if (flag)
        {
            roll += 5.0;
        }
        else
        {            
            roll -= 5.0;
        }
        flag = !flag;
    }
}






















