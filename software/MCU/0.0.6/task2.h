

   #define HELLO_URI   "/hello"
    #define PARAM_STYLE "/style.json"


  
void serverTask(void *parameters){
  for(;;){
    Portal.handleClient();
    vTaskDelay(10);  // one tick delay (15ms) in between reads for stability
  }
}
