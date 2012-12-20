#ifndef ARPFINGERPRINT_H
#define ARPFINGERPRINT_H

#include <sstream>

#define MAX_RECORDED_REPLIES 10

struct ArpFingerprint
{
	/* This is true if the host sends a TCP response before sending an ARP packet.
	 This might need to be expanded more though. Linux seems to reply if the ARP entry
	 is in the ARP cache but has become stale, but not if it isn't in the cache at all */
	bool replyBeforeARP;

	/* Did we get unicast or multicast requests*/
	/* TODO: Handle the case where we got some combination of both? */
	bool unicastRequest;

	/* Saw a TCP response even though we didn't reply with ARP */
	bool sawResponse;

	/* Number of attempts to resolve the ARP address */
	int arpRequests;

	/* Timing between ARP requests */
	int timeBetweenRequests[MAX_RECORDED_REPLIES];
	double averageTimeBetweenRequests;

	ArpFingerprint()
	{
		arpRequests = 0;
		sawResponse = false;
		averageTimeBetweenRequests = -1;

		for (int i = 0; i < 10; i++)
			timeBetweenRequests[i] = -1;
	}

	std::string toString()
	{
		std::stringstream ss;
		ss << "Saw TCP response when no ARP reply         : " << std::boolalpha << sawResponse << std::endl;
		ss << "Replied before ARP request                 : " << std::boolalpha << replyBeforeARP << std::endl;
		ss << "Send unicast ARP request                   : " << std::boolalpha << unicastRequest << std::endl;
		ss << "Number of ARP Requests before giving up    : " << arpRequests << std::endl;
		ss << "Average time between each request (ms)     : " << averageTimeBetweenRequests << std::endl;

		ss << "Time between ARP attempts                  : ";
		for (int i = 0; i < arpRequests - 1; i++)
			ss << timeBetweenRequests[i] << " ";
		ss << std::endl;

		return ss.str();
	}
};


#endif