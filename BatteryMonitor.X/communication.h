/* 
 * File:   communication.h
 * Author: Kevin
 *
 * Created on 26 juin 2015, 12:12
 */

#ifndef COMMUNICATION_H
#define	COMMUNICATION_H

void comConfig(void);
int comIsConnected(void);
int comSendMessage(int state, float data);
void comSendId(void);
void resetSampleCounter(void);



#endif	/* COMMUNICATION_H */

