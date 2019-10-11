
    WebServer Servidor;
AutoConnect       Portal(Servidor);
AutoConnectConfig Config;       // Enable autoReconnect supported on v0.9.4
AutoConnectAux    Timezone;
    

   #define HELLO_URI   "/hello"
    #define PARAM_STYLE "/style.json"



float Temperature = 0 ;
float Humidity = 31;

  
void serverTask(void *parameter){
     for(;;){
      yield();
  }
  vTaskDelay(10);  // one tick delay (15ms) in between reads for stability
}
