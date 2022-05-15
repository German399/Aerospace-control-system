    ///пример использования udp.h. CDpackIN - инициализированная структура
    /// char *buffer= (char*)malloc(sizeof(CDpackIN));
	/// memcpy(buffer,(const char*)&CDpackIN,sizeof(CDpackIN));
    /// udpSend(buffer,sizeof(CDpackIN),"195.19.46.45",6100);
    /// free(buffer);
#include <stdint.h>
bool udpSend(const char *msg,size_t len ,const char *HOSTNAME, uint16_t PORT);
