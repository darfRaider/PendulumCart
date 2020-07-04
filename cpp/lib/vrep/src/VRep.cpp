/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VRep.cpp
 * Author: sam
 * 
 * Created on July 3, 2020, 12:10 PM
 */

#include "VRep.hpp"

VRep::VRep(int port, const simxChar* ip):
  port(port),
  ip(ip){
}

VRep::~VRep() {
}

void VRep::connect(){ 
  clientID = simxStart(ip,port,true,true,2000,5);
  if( clientID != -1 ){
    printf("Connected to remote API server\n");    
  }
  else {
    printf("Unable to connect.\n");  
  }
}

void VRep::disconnect(){
  simxFinish(clientID);
}

int VRep::getClientID(){
  return clientID;
}

void VRep::StartSimulation(){
  simxStartSimulation(clientID,simx_opmode_oneshot);
}

void VRep::StopSimulation(){
  simxStopSimulation(clientID,simx_opmode_blocking);
}
