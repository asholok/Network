#include "NetworkException.h"

NetworkException::NetworkException(int id) {
	if ( id == 1 ) {
		error = "Wrong Ipadress Format!!";
	} else if ( id == 2 ) {
		error = "Wrong Mask Format!!";
	} else {
		error = "Unnone error ID!!";
	}
}