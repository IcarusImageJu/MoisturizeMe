//    debugA("This is a any (always showed) - var %d", var);
//    debugV("This is a verbose - var %d", var);
//    debugD("This is a debug - var %d", var);
//    debugI("This is a information - var %d", var);
//    debugW("This is a warning - var %d", var);
//    debugE("This is a error - var %d", var);

#ifndef DEBUG_DISABLED
  // Process commands from RemoteDebug
  void processCmdRemoteDebug() {
    String lastCmd = Debug.getLastCommand();
    if (lastCmd == "bench1") {
      // Benchmark 1 - Printf
      debugA("* Benchmark 1 - one Printf");
      uint32_t timeBegin = millis();
      uint8_t times = 50;
      for (uint8_t i = 1; i <= times; i++) {
        debugA("%u - 1234567890 - AAAA", i);
      }
      debugA("* Time elapsed for %u printf: %ld ms.\n", times,
            (millis() - timeBegin));
    } else if (lastCmd == "bench2") {
      // Benchmark 2 - Print/println
      debugA("* Benchmark 2 - Print/Println");
      uint32_t timeBegin = millis();
      uint8_t times = 50;
      for (uint8_t i = 1; i <= times; i++) {
        if (Debug.isActive(Debug.ANY)) {
          Debug.print(i);
          Debug.print(" - 1234567890");
          Debug.println(" - AAAA");
        }
      }
      debugA("* Time elapsed for %u printf: %ld ms.\n", times,
            (millis() - timeBegin));
    }
  }
#endif

void setupDebug(){
      #ifndef DEBUG_DISABLED // Only for development
    // Initialize RemoteDebug
    Debug.begin(HOST_NAME); // Initialize the WiFi server
    //Debug.setPassword("r3m0t0."); // Password for WiFi client connection (telnet or webapp)  ?
    Debug.setResetCmdEnabled(true); // Enable the reset command
    Debug.showProfiler(true); // Profiler (Good to measure times, to optimize codes)
    Debug.showColors(true); // Colors
    // Debug.setSerialEnabled(true); // if you wants serial echo - only recommended if ESP is plugged in USB
    // Project commands
    String helpCmd = "bench1 - Benchmark 1\n";
    helpCmd.concat("bench2 - Benchmark 2");
    Debug.setHelpProjectsCmds(helpCmd);
    Debug.setCallBackProjectCmds(&processCmdRemoteDebug);
    // End of setup - show IP
    Serial.println("* Arduino RemoteDebug Library");
    Serial.println("*");
    Serial.print("* WiFI connected. IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("*");
    Serial.println("* Please use the telnet client (telnet for Mac/Unix or putty and others for Windows)");
    Serial.println("* or the RemoteDebugApp (in browser: http://joaolopesf.net/remotedebugapp)");
    Serial.println("*");
    Serial.println("* This sample will send messages of debug in all levels.");
    Serial.println("*");
    Serial.println("* Please try change debug level in client (telnet or web app), to see how it works");
    Serial.println("*");
  #endif
}

uint32_t timeBeginLoop;

void preLoopDebug() {
  #ifndef DEBUG_DISABLED
    // Time of begin of this loop
    timeBeginLoop = millis();
  #endif
}

void loopDebug() {
  #ifndef DEBUG_DISABLED
    // RemoteDebug handle (for WiFi connections)
    Debug.handle();
  #endif
}

void postLoopDebug() {
  #ifndef DEBUG_DISABLED
    // Show a debug - warning if time of these loop is over 50 (info) or 100 ms (warning)
    uint32_t time = (millis() - timeBeginLoop);
    if (time > 100) {
      debugI("* Time elapsed for the loop: %u ms.", time);
    } else if (time > 200) {
      debugW("* Time elapsed for the loop: %u ms.", time);
    }
  #endif
}

