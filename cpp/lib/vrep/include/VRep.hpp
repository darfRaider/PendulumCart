/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VRep.hpp
 * Author: sam
 *
 * Created on July 3, 2020, 12:10 PM
 */

#ifndef VREP_HPP
#define VREP_HPP

#include <iostream>
extern "C" {
    #include "extApi.h"
}

class VRep {
public:
  /**
   * @brief Default constructor.
   *
   * @param port Port to V-REP client
   * @param ip IP of V-REP client
   */
    VRep(int port = 19997, const char* ip = "127.0.0.1");
    virtual ~VRep();
    
	/**
	 * @brief Connect to V-REP client.
	 */
    void connect();

	/**
	 * @brief Disconnect from V-REP client.
	 */
    void disconnect();
    
    int getClientID();
    
    void StartSimulation();
    void StopSimulation();
    
private:
    int clientID;
	
    // Connection parameters	
    const int port;
    const char* ip;
    const bool waitUntilConnected = true;
    const bool doNotReconnectOnceDisconnected = true;
    const int timeOutInMs = 2000;
    const int commThreadCycleInMs = 5;
};

#endif /* VREP_HPP */

