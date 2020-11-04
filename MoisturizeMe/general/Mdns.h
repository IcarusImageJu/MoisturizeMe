void setupMdns(){
      #if defined USE_MDNS && defined HOST_NAME
    if (MDNS.begin(HOST_NAME)) {
      Serial.print("* MDNS responder started. Hostname -> ");
      Serial.println(HOST_NAME);
    }
    // Register the services
    #ifndef DEBUG_DISABLED
      MDNS.addService("telnet", "tcp", 23); // Telnet server of RemoteDebug, register as telnet
    #endif
  #endif // MDNS
}