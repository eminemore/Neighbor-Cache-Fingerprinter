#include "ArpFingerprint.h"

using namespace std;

ArpFingerprint::ArpFingerprint() {
	requestAttemptsMin = 999;
	requestAttemptsMax = -1;
	maxTimeBetweenRetries = 0;
	minTimeBetweenRetries = 0;
	constantRetryTime = false;
	referencedStaleTimeout = 0;
	replyBeforeUpdate = false;
	unicastUpdate = false;


	for (int i = 0; i < 36; i++)
		gratuitousUpdates[i] = false;
}

// Loads in the 1 line string generated by toTinyString()
ArpFingerprint::ArpFingerprint(std::string tinyString) {
	stringstream ss(tinyString);
	ss >> requestAttemptsMin;
	ss >> requestAttemptsMax;
	ss >> minTimeBetweenRetries;
	ss >> maxTimeBetweenRetries;
	ss >> constantRetryTime;
	ss >> referencedStaleTimeout;
	ss >> replyBeforeUpdate;
	ss >> unicastUpdate;

	for (int i = 0; i < 36; i++) {
		ss >> gratuitousUpdates[i];
	}
}
// Convert to a 1 line string suitable for storage
string ArpFingerprint::toTinyString() {
	stringstream ss;

	ss << requestAttemptsMin << " ";
	ss << requestAttemptsMax << " ";
	ss << minTimeBetweenRetries << " ";
	ss << maxTimeBetweenRetries << " ";
	ss << constantRetryTime << " ";
	ss << referencedStaleTimeout << " ";
	ss << replyBeforeUpdate << " ";
	ss << unicastUpdate << " ";

	for (int i = 0; i < 36; i++) {
		ss << gratuitousUpdates[i] << " ";
	}

	return ss.str();
}

// User readable string
string ArpFingerprint::toString() {
	stringstream ss;
	ss << "Min Number of ARP Requests Seen            : " << requestAttemptsMin << endl;
	ss << "Max Number of ARP Requests Seen            : " << requestAttemptsMax << endl;
	ss << "Min time between ARP retries  (ms)         : " << minTimeBetweenRetries << endl;
	ss << "Max time between ARP retries  (ms)         : " << maxTimeBetweenRetries << endl;
	ss << "Constant retry between attempts            : " << boolalpha << constantRetryTime << endl;
	ss << "Stale timeout value                        : " << referencedStaleTimeout << endl;
	ss << "Replied before ARP request                 : " << boolalpha << replyBeforeUpdate << endl;
	ss << "Got unicast instead of bcast request       : " << boolalpha << unicastUpdate << endl;

	ss << "Gratuitous probe result fingerprint        : ";
	for (int i = 0; i < 36; i++) {
		if (gratuitousUpdates[i]) {
			ss << "1";
		} else {
			ss << "0";
		}
	}

	ss << endl;

	return ss.str();
}


bool ArpFingerprint::operator !=(const ArpFingerprint &rhs) const {
	return !(operator ==(rhs));
}

bool ArpFingerprint::operator ==(const ArpFingerprint &rhs) const {
	if (requestAttemptsMin != rhs.requestAttemptsMin)
		return false;

	if (requestAttemptsMax != rhs.requestAttemptsMax)
		return false;

	if (minTimeBetweenRetries != rhs.minTimeBetweenRetries)
		return false;

	if (maxTimeBetweenRetries != rhs.maxTimeBetweenRetries)
		return false;

	if (constantRetryTime != rhs.constantRetryTime)
		return false;

	if (referencedStaleTimeout != rhs.referencedStaleTimeout)
		return false;

	if (replyBeforeUpdate != replyBeforeUpdate)
		return false;

	if (unicastUpdate != rhs.unicastUpdate)
		return false;

	for (int i = 0; i < 36; i++) {
		if (gratuitousUpdates[i] != rhs.gratuitousUpdates[i]) {
			return false;
		}
	}

	return true;
}

