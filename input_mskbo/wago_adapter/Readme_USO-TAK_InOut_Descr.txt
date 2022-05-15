//=====================================================================================================================
29.04.2021г. Сухомлинов А.Б.
Обмен по UDP-сокету между БРЭО-МСКБО и УСО-ТАК_WAGO
//=====================================================================================================================

Сокет UDP БРЭО-МСКБО --> УСО-ТАК_WAGO :

  type = SOCK_DGRAM
  ip   = "192.168.1.55"
  port = 6011 == USO_TAK_IN_PORT

  #define TUsoTakNetIn  TFD_WAGO_Inputs  // Входные данные Кабины : УСО-WAGO <== БРЭО-МСКБО

  TUsoTakNetIn  rt2usoTakData;   // [100 байт] входные параметры для модели УСО-ТАК (WAGO)
  
  cntS++;
  rt2usoTakData = rt2uso.data;
  rt2usoTakData.idpack = 0x61;   // [2] идентификатор пакета == 0x0061
  rt2usoTakData.szbuf  = 92;     // [2] размер буфера данных пакета [байт]
  rt2usoTakData.step   = cntS;   // [4] шаг счета СПНМ-МСКБО
  
  rc = sendto( serv_sock, (char*)&rt2usoTakData, sizeof(rt2usoTakData), 0, (LPSOCKADDR)&serv_addr, addr_len );
  


//=====================================================================================================================

Сокет UDP БРЭО-МСКБО <-- УСО-ТАК_WAGO :

  type = SOCK_DGRAM
  ip   = INADDR_ANY
  port = 6021 == USO_TAK_OUT_PORT

  #define TUsoTakNetOut  TFD_WAGO_Outputs  // Выходные данные Кабины : УСО-WAGO ==> БРЭО-МСКБО (ММ_ЛА и в БРЭО)

  TUsoTakNetOut  usoTak2rtData;  // [356 байт] выходные параметры от модели УСО-ТАК (WAGO)

  
  rc = recvfrom(serv_sock, (char*)&usoTak2rtData, sizeof(usoTak2rtData), 0, (LPSOCKADDR)&serv_addr, &addr_len);

  //usoTak2rtData.idpack = 0x62;   // [2] идентификатор пакета == 0x0062
  //usoTak2rtData.szbuf  = 348;    // [2] размер буфера данных пакета [байт]
  //usoTak2rtData.step   = cntR;   // [4] шаг счета УСО-ТАК

//=====================================================================================================================
