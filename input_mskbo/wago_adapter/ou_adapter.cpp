//собирать 32 битным компилятором(x86) MVSC 2019 
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/asio.hpp>

#include <boost/array.hpp>
#include <boost/bind.hpp>

#include <thread>
#include <iostream>
#include <fstream>
#include "UsoTakNet_IOTypes.h"

#include "hiredis.h"
#define STREAM_NAME "MSKBO_input"
        redisContext *c;
        redisReply *reply;
        const char *hostname = "mskbo";
        int port = 49153;
        struct timeval timeout = { 1, 500000 }; // 1.5 seconds
        ///Статистические переменные, необходимые для отслеживая корректности показаний WAGO
        ///переменные вертолета имеют возможность триммирования, при помощи электромеханизма. 
        ///Первые 100 показаний усредняются при старте программы и помещаются в trim-переменные
        ///если была нажата кнопка тримированния, собираются сто показаний после её нажатия и усредняются
        unsigned short int psi_min,psi_max,psi_average, psi_trim;
        unsigned short int gam_min,gam_max,gam_average, gam_trim;
        unsigned short int tng_min,tng_max,tng_average, tng_trim;
        unsigned short int gaz1_min,gaz1_max,gaz1_average, gaz1_normalized;
        unsigned short int gaz2_min,gaz2_max,gaz2_average, gaz2_normalized;
        unsigned short int shag_vint_min,shag_vint_max,shag_vint_average,shag_vint_normalized;
        //переменные самолета(сайдстики)

        
#include <nlohmann/json.hpp>
using json = nlohmann::json;
json J_LA;

#define IPADDRESS "192.168.1.10" // "192.168.1.64"
#define WAGOip "192.168.1.26"//192.168.1.55

#define WAGOportIn 6011
#define WAGOportStrIn "6011"
#define WAGOportOut 6021
#define WAGOportStrOut "6021"
using boost::asio::ip::udp;
using boost::asio::ip::address;




struct FromWAGO {
    boost::asio::io_service io_service;
    udp::socket socket{io_service};
    boost::array<char, sizeof(TUsoTakNetOut)> recv_buffer;
    //udp::endpoint remote_endpoint;
    udp::endpoint wago2adapter_endpoint = udp::endpoint(udp::v4(), WAGOportOut);
    int count = 100;
    //std::ofstream myfile;
        
    void handle_receive(const boost::system::error_code& error, size_t bytes_transferred) {
        if (error) {
            std::cout << "Receive failed: " << error.message() << "\n";
            return;
        }
        
        //int len=sizeof(TUsoTakNetOut);
        
        //TUsoTakNetOut  Outbuf;
        //char* dataOut = (char*)malloc(sizeof(TUsoTakNetOut));
        char* databuf = (char*)malloc(sizeof(TUsoTakNetOut));
        databuf = recv_buffer.c_array();
        TUsoTakNetOut dataOut;
        //memcpy((const char*)&dataOut, databuf, sizeof(TUsoTakNetOut));
        memcpy(&dataOut, databuf, sizeof(TUsoTakNetOut));
        
       // memcpy(&Outbuf,&tempbuf,len);
        //std::cout << "stepnum="<<Outbuf.step <<"psi="<< Outbuf.ao_code.aoFltCtrl.psi << "gam="<<Outbuf.ao_code.aoFltCtrl.gam<< "tng="<< Outbuf.ao_code.aoFltCtrl.tng<< "shv="<<Outbuf.ao_code.aoFltCtrl.shv<< "gaz1,2=" << Outbuf.ao_code.aoFltCtrl.gaz_1<<" " << Outbuf.ao_code.aoFltCtrl.gaz_2<<"\n";;
        std::cout << "sizeofstruct_unpacked="<< sizeof(dataOut)<< " packid="<< dataOut.idpack  <<" size0fidpack="<<sizeof(dataOut.idpack)<<"total size pack="<<sizeof(dataOut) <<" szfub="<< dataOut.szbuf<<" size0f="<<sizeof(dataOut.szbuf)<<"\n";
        std::cout << " step=" << dataOut.step<< "di_bits=" << dataOut.di_bits.btnPUPKV.ap <<"\n";
        //memccpy((),Outbuf, (sizeof(TUsoTakNetOut)));
        //TUsoTakNetOut FromWagoStruct = reinterpret_cast<TUsoTakNetOut*>(recv_buffer.c_array());
        std::cout << " Received: '" << std::string(recv_buffer.begin(), recv_buffer.begin()+bytes_transferred) << "' (" << error.message() << ")\n";
        
        std::string setstr="SET "+std::string(recv_buffer.begin(), recv_buffer.begin()+bytes_transferred);
        //min 0 max 65535
        //remote_
        //копируем данные из входного пакета
        J_LA["raw"]["helicopter"]["psi"] = (int)dataOut.ao_norm.aoFltCtrl.psi;
        J_LA["raw"]["helicopter"]["gam"] = (int)dataOut.ao_norm.aoFltCtrl.gam;
        J_LA["raw"]["helicopter"]["tng"] = (int)dataOut.ao_norm.aoFltCtrl.tng;
        ///J_LA["raw"]["helicopter"]["trim"] накапливает значения при старте(первые 10 тиков работы программы)
        ///При смене
        J_LA["raw"]["helicopter"]["trim"]["psi"] = (int)dataOut.ao_norm.aoFltCtrl.psi;
        J_LA["raw"]["helicopter"]["trim"]["gam"] = (int)dataOut.ao_norm.aoFltCtrl.gam;
        J_LA["raw"]["helicopter"]["trim"]["tng"] = (int)dataOut.ao_norm.aoFltCtrl.tng;
        J_LA["raw"]["helicopter"]["gaz1"] = (int)dataOut.ao_norm.aoFltCtrl.gaz_1;
        J_LA["raw"]["helicopter"]["gaz2"] = (int)dataOut.ao_norm.aoFltCtrl.gaz_2;
        J_LA["raw"]["helicopter"]["shag_vint"] = (int)dataOut.ao_norm.aoFltCtrl.shv;

        J_LA["raw"]["airplane"]["zakr"]= (int)dataOut.ao_norm.aoCentCons.zakr;
        J_LA["raw"]["airplane"]["sidestick_1"]["gam"]= (int)dataOut.ao_norm.aoStick1.gam;
        J_LA["raw"]["airplane"]["sidestick_1"]["knkLR"]= (int)dataOut.ao_norm.aoStick1.knpLR;
        J_LA["raw"]["airplane"]["sidestick_1"]["knpUD"]= (int)dataOut.ao_norm.aoStick1.knpUD;
        J_LA["raw"]["airplane"]["sidestick_1"]["MRK"]= (int)dataOut.ao_norm.aoStick1.MRK;
        J_LA["raw"]["airplane"]["sidestick_1"]["tng"]= (int)dataOut.ao_norm.aoStick1.tng;

        J_LA["raw"]["airplane"]["sidestick_2"]["gam"]= (int)dataOut.ao_norm.aoStick2.gam;
        J_LA["raw"]["airplane"]["sidestick_2"]["knkLR"]= (int)dataOut.ao_norm.aoStick2.knpLR;
        J_LA["raw"]["airplane"]["sidestick_2"]["knpUD"]= (int)dataOut.ao_norm.aoStick2.knpUD;
        J_LA["raw"]["airplane"]["sidestick_2"]["MRK"]= (int)dataOut.ao_norm.aoStick2.MRK;
        J_LA["raw"]["airplane"]["sidestick_2"]["tng"]= (int)dataOut.ao_norm.aoStick2.tng;

        
        ///получить входные данные из структуры MSKBO_control
        ///1.поместить данные от MSKBO_control в do_bits
        ///выполняется в передаче в структуре dataIn
        ///2.проверить на следующем шаге и передать в J_LA[ctrl]
/*         J_LA["lamp"]["leftOvrHeadCons"]["baka_1"] = (int)dataOut.do_bits.leftOvrHeadCons.baka_1;
        J_LA["lamp"]["leftOvrHeadCons"]["baka_2"] = (int)dataOut.do_bits.leftOvrHeadCons.baka_2;
        J_LA["lamp"]["leftOvrHeadCons"]["baka_rashod"] = (int)dataOut.do_bits.leftOvrHeadCons.raskhod_baka;
        J_LA["lamp"]["leftOvrHeadCons"]["generator_vklyuchen"] = (int)dataOut.do_bits.leftOvrHeadCons.generator_vklyuchen;
        J_LA["lamp"]["leftOvrHeadCons"]["pos_vklyuchen"] = (int)dataOut.do_bits.leftOvrHeadCons.pos_vklyuchen;
        J_LA["lamp"]["leftOvrHeadCons"]["vklyuchi_pos"] = (int)dataOut.do_bits.leftOvrHeadCons.vklyuchi_pos;
        J_LA["lamp"]["leftTriPan"]["obogrev_svvd_ispraven"] = (int)dataOut.do_bits.leftTriPan.obogrev_svvd_ispraven; */
         J_LA["lamp"]["leftOvrHeadCons"]["baki_1_2"] = (int)dataOut.di_bits.leftOvrHeadCons.baki_1_2;
         J_LA["lamp"]["leftOvrHeadCons"]["lev_dvig_ruchn"] = (int)dataOut.di_bits.leftOvrHeadCons.lev_dvig_ruchn;
         //TODO
        if(((int)dataOut.do_bits.lmpPUPKV.dw32)!=0){J_LA["lamp"]["lmpPUPKV"]["ALL"] = (int)dataOut.do_bits.lmpPUPKV.dw32;}
        else{  
        //J_LA["lamp"]["lmpPUPKV"]["ap"] = (int)dataOut.do_bits.lmpPUPKV.ap;
        J_LA["lamp"]["lmpPUPKV"]["ap"] = (int)dataOut.di_bits.btnPUPKV.ap;
        J_LA["lamp"]["lmpPUPKV"]["avt_trim"] = (int)dataOut.do_bits.lmpPUPKV.avt_trim;
        J_LA["lamp"]["lmpPUPKV"]["avt_upr"] = (int)dataOut.do_bits.lmpPUPKV.avt_upr;
        J_LA["lamp"]["lmpPUPKV"]["dir_upr"] = (int)dataOut.do_bits.lmpPUPKV.dir_upr;
        J_LA["lamp"]["lmpPUPKV"]["dovor"] = (int)dataOut.do_bits.lmpPUPKV.dovor;
        J_LA["lamp"]["lmpPUPKV"]["goriz"] = (int)dataOut.do_bits.lmpPUPKV.goriz;
        J_LA["lamp"]["lmpPUPKV"]["goriz"] = (int)dataOut.di_bits.btnPUPKV.goriz;
        J_LA["lamp"]["lmpPUPKV"]["h_bar"] = (int)dataOut.do_bits.lmpPUPKV.h_bar;
        J_LA["lamp"]["lmpPUPKV"]["h_rv"] = (int)dataOut.do_bits.lmpPUPKV.h_rv;
        J_LA["lamp"]["lmpPUPKV"]["mal_skor"] = (int)dataOut.do_bits.lmpPUPKV.mal_skor;
        J_LA["lamp"]["lmpPUPKV"]["marshr"] = (int)dataOut.do_bits.lmpPUPKV.marshr;
        J_LA["lamp"]["lmpPUPKV"]["mvp"] = (int)dataOut.do_bits.lmpPUPKV.mvp;
        J_LA["lamp"]["lmpPUPKV"]["parir"] = (int)dataOut.do_bits.lmpPUPKV.parir;
        J_LA["lamp"]["lmpPUPKV"]["pg"] = (int)dataOut.do_bits.lmpPUPKV.pg;
        J_LA["lamp"]["lmpPUPKV"]["posad"] = (int)dataOut.do_bits.lmpPUPKV.posad;
        J_LA["lamp"]["lmpPUPKV"]["ugl_skor"] = (int)dataOut.do_bits.lmpPUPKV.ugl_skor;
        J_LA["lamp"]["lmpPUPKV"]["ugol"] = (int)dataOut.do_bits.lmpPUPKV.ugol;
        J_LA["lamp"]["lmpPUPKV"]["v_pr"] = (int)dataOut.do_bits.lmpPUPKV.v_pr;
        J_LA["lamp"]["lmpPUPKV"]["visen"] = (int)dataOut.do_bits.lmpPUPKV.visen;
        J_LA["lamp"]["lmpPUPKV"]["zakhod"] = (int)dataOut.do_bits.lmpPUPKV.zakhod;
        }
        J_LA["lamp"]["rightInstrPan"]["shassi"] =  (int)dataOut.do_bits.rightInstrPan.shassi;
        J_LA["lamp"]["rightOvrHeadCons"]["otkaz_lev_akkum"] =  (int)dataOut.do_bits.rightOvrHeadCons.otkaz_lev_akkum;
        J_LA["lamp"]["rightOvrHeadCons"]["otkaz_lev_generatora"] =  (int)dataOut.do_bits.rightOvrHeadCons.otkaz_lev_generatora;
        J_LA["lamp"]["rightOvrHeadCons"]["otkaz_prav_akkum"] =  (int)dataOut.do_bits.rightOvrHeadCons.otkaz_prav_akkum;
        J_LA["lamp"]["rightOvrHeadCons"]["otkaz_prav_generatora"] =  (int)dataOut.do_bits.rightOvrHeadCons.otkaz_prav_generatora;
        J_LA["lamp"]["rightOvrHeadCons"]["rozetka_vklyuchena"] =  (int)dataOut.do_bits.rightOvrHeadCons.rozetka_vklyuchena;
        J_LA["lamp"]["rightTriPan"]["generator_otklyuchen"] =  (int)dataOut.do_bits.rightTriPan.generator_otklyuchen;
        J_LA["lamp"]["rightTriPan"]["pzu_vklyuchen"] =  (int)dataOut.do_bits.rightTriPan.pzu_vklyuchen;
        
        ///...
        if(dataOut.ao_norm.aoFltCtrl.psi>0){J_LA["ctrl"]["helicopter"]["psi"] = dataOut.ao_norm.aoFltCtrl.psi/65535;}else{J_LA["ctrl"]["helicopter"]["psi"] = 0;};
        if(dataOut.ao_norm.aoFltCtrl.gam>0){J_LA["ctrl"]["helicopter"]["gam"] = dataOut.ao_norm.aoFltCtrl.gam/65535;}else{J_LA["ctrl"]["helicopter"]["gam"] = 0;};
        if(dataOut.ao_norm.aoFltCtrl.tng>0){J_LA["ctrl"]["helicopter"]["tng"] = dataOut.ao_norm.aoFltCtrl.tng/65535;}else{J_LA["ctrl"]["helicopter"]["tng"]=0;};
        


        if(dataOut.ao_norm.aoFltCtrl.psi>0){J_LA["axis"]["X"] = dataOut.ao_norm.aoFltCtrl.psi/65535;}else{dataOut.ao_norm.aoFltCtrl.psi=0;};
        if(dataOut.ao_norm.aoFltCtrl.gam>0){J_LA["axis"]["Y"] = dataOut.ao_norm.aoFltCtrl.gam/65535;}else{dataOut.ao_norm.aoFltCtrl.gam=0;};
        if(dataOut.ao_norm.aoFltCtrl.tng>0){J_LA["axis"]["Z"] = dataOut.ao_norm.aoFltCtrl.tng/65535;}else{dataOut.ao_norm.aoFltCtrl.tng=0;};

        //if(dataOut.ao_norm.aoFltCtrl.psi>0){J_LA["rot"]["X"] = dataOut.ao_norm.aoFltCtrl.psi/65535;};
        //if(dataOut.ao_norm.aoFltCtrl.gam>0){J_LA["rot"]["Y"] = dataOut.ao_norm.aoFltCtrl.gam/65535;};
        //if(dataOut.ao_norm.aoFltCtrl.gam>0){J_LA["rot"]["Z"] = dataOut.ao_norm.aoFltCtrl./65535;};
        std::cout <<"j_la["<< dataOut.step<<"]: " << J_LA.dump() << "\n";
        //если у нас есть данные, записываем их в JSON структуру
       // reply = (redisReply *)redisCommand(c,J_LA.dump().c_str());
    
        if (reply != NULL){
        //FromDBdata = json::parse(reply->str);
        //send data to db
        //
        freeReplyObject(reply);
        }
        //накопление статистики - мин, макс, средн, нейтрал
        if (--count > 0) {
            std::cout << "Count: " << count << "\n";
            wait();
        }
    }

    void wait() {
        socket.async_receive_from(boost::asio::buffer(recv_buffer),
            wago2adapter_endpoint,
            boost::bind(&FromWAGO::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            
    }

    void Receiver()
    {
        socket.open(udp::v4());
        socket.bind(wago2adapter_endpoint);

        wait();

        std::cout << "Receiving\n";
        io_service.run();
        std::cout << "Receiver exit\n";
    }
};

int main()
{
    FromWAGO client;
    //client.myfile.open("output.txt");
    std::thread r([&] { client.Receiver(); });
    
    
    TNET_U32 cntS=0;
    //while

   
    //auto size=sizeof(&rt2usoTakData);
    //char init_pack[sizeof(TUsoTakNetIn)]; 
    //char* init_pack = reinterpret_cast<char*>(&rt2usoTakData);


    //init_pack = reinterpret_cast<char (&)[sizeof(TUsoTakNetIn)]>(rt2usoTakData);
    //memcpy(rt2usoTakData,&init_pack,sizeof(TUsoTakNetIn));
    //boost::asio::streambuf buf;
    //std::ostream os(&buf);
    //boost::archive::binary_oarchive out_archive(os);
    //out_archive << rt2usoTakData;
    
//  rt2usoTakData

    
    //std::string input(sizeof(TUsoTakNetIn), init_pack);
    //std::string input = reinterpret_cast<char(*)[sizeof(TUsoTakNetIn)]>rt2usoTakData;
    //std::string input = init_pack;
    //uf.data;
   

    static TUsoTakNetIn* rt2usoTakData = new TUsoTakNetIn;
    boost::asio::io_service io_service;
    udp::socket socket(io_service);
    udp::endpoint remote_endpoint_WAGOin = udp::endpoint(address::from_string(WAGOip), WAGOportIn);
    udp::endpoint remote_endpoint_WAGOout = udp::endpoint(address::from_string(WAGOip), WAGOportIn);
    socket.open(udp::v4());
    boost::system::error_code err;
    for (int i = 0; i < 51; ++i) {
        //std::thread r([&] { client.(); });
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
            cntS++;
            rt2usoTakData->step = cntS;
            rt2usoTakData->do_bits.leftOvrHeadCons.dw32=0x0;		
            rt2usoTakData->do_bits.leftTriPan.dw32 =0x0;
            rt2usoTakData->do_bits.lmpPUPKV.dw32 = 0x1;
            rt2usoTakData->do_bits.lmpPUPKV.ap = 0x1;
            rt2usoTakData->do_bits.lmpPUPKV.avt_upr = 0x1;
            rt2usoTakData->do_bits.lmpPUPKV.marshr = 0x1;
            //rt2usoTakData->do_bits.lmpPUPKV.zakhod = 0x1;
            rt2usoTakData->do_bits.rightInstrPan.dw32 = 0x0;
            rt2usoTakData->do_bits.rightOvrHeadCons.dw32 = 0x0;
            rt2usoTakData->do_bits.rightTriPan.dw32 = 0x0;
            rt2usoTakData->wagoCtrl.connected_to_couplers = 0x1;
            rt2usoTakData->wagoCtrl.window_visible = 0x1;
            rt2usoTakData->wagoCtrl.res3203 = 0x0;
            for (int j = 0; j <= 15; j++) {
                rt2usoTakData->wagoCtrl.dw32_res[j]=0x0;
            };
            //rt2usoTakData.TFD_InD_WAGO_Ctrl wagoCtrl;		
            rt2usoTakData->indics.aiRtOvrHdCons.ark_freq = 444.6666;			
            rt2usoTakData->idpack = 0x61;   
            rt2usoTakData->szbuf = 92;     
        
       /*  if(i>50)
        {
        rt2usoTakData->wagoCtrl.dw32 = 0x0;
        rt2usoTakData->do_bits.lmpPUPKV.avt_upr = 0x1;
        rt2usoTakData->do_bits.lmpPUPKV.marshr = 0x1;
        rt2usoTakData->do_bits.lmpPUPKV.zakhod = 0x0;
        rt2usoTakData->do_bits.leftOvrHeadCons.baka_1 = 0x1;
        rt2usoTakData->do_bits.leftOvrHeadCons.baka_2 = 0x1;
        rt2usoTakData->do_bits.leftOvrHeadCons.generator_vklyuchen = 0x1;
        rt2usoTakData->do_bits.leftOvrHeadCons.raskhod_baka = 0x1;
        rt2usoTakData->do_bits.lmpPUPKV.marshr = 0x0;
        rt2usoTakData->do_bits.lmpPUPKV.zakhod = 0x0;
        
        } */
        //rt2usoTakData.step = cntS;
        //динамическая проверка ламп
        //rt2usoTakData.do_bits.lmpPUPKV.avt_upr = 0x1;
        //rt2usoTakData.do_bits.lmpPUPKV.marshr = 0x1;
        //rt2usoTakData.do_bits.lmpPUPKV.zakhod = 0x1;
        //char* init_pack = reinterpret_cast<char*>(&rt2usoTakData);
        std::cout << "Input is '" << rt2usoTakData << "'\nSending it to Sender Function...\n";


        //send_pack = (char *)malloc(sizeof(*rt2usoTakData));
        //send_pack =const_cast<TUsoTakNetIn*>(rt2usoTakData);
        //memcpy(&send_pack, &rt2usoTakData, sizeof(TUsoTakNetIn));
        //char buffer[sizeof(i)];
        //memcpy(send_pack, rt2usoTakData, sizeof(TUsoTakNetIn));
        //memcpy(&j, buffer, sizeof(TUsoTakNetIn));
        //std::string sIn = (sizeof(TUsoTakNetIn),reinterpret_cast<char*>(rt2usoTakData));
        //int size_wago_in = sizeof(TUsoTakNetIn);
        //std::string sIn = convertToString(send_pack, a_size);
        //char* const buf = reinterpret_cast<char*>(&rt2usoTakData);
        //std::string sIn = (sizeof(TUsoTakNetIn),send_pack);
        
        //std::string s
        //s.resize(100);
        //s.c_str = send_pack;

        
        //std::string sIn(100,rt2usoTakData);
        //sIn =   &rt2usoTakData;        //boost::asio::buffer_cast()
        //std::string sIn = buf;
        const char * InBuf = (char*)&rt2usoTakData;

    //boost::asio::streambuf sb;
    //std::ostream os(&sb);
    //os.write(in, sizeof(TUsoTakNetIn));
        char* data = (char*)malloc(sizeof(TUsoTakNetIn));
        memcpy(data, rt2usoTakData, sizeof(TUsoTakNetIn));
        auto sent = socket.send_to(boost::asio::buffer(data, sizeof(TUsoTakNetIn)), remote_endpoint_WAGOout, 0, err);
        
        std::cout << "Sent Payload --- " << sent << "\n";
        //Sender(InBuf);
        //free(send_pack);
        //free(data);
    }
    
    r.join();
    socket.close(); 
    return 0;
}