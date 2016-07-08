#include "communication.h"

Communication::Communication()
{
	imgData = (unsigned char *)malloc(IMG_WIDTH*IMG_HEIGHT*3*2);
	
	context = zmq_init(1);
	responder = zmq_socket(context, ZMQ_REP);
	zmq_bind(responder, "tcp://*:5555");
}

Communication::~Communication()
{
	// We never get here but if we did, this would be how we end
	zmq_close(responder);
	zmq_term(context);
}

void Communication::Run(unsigned char *mat1, unsigned char *mat2, int pts[18])
{
	while(1) {
		// Wait for next request from client
		zmq_msg_t request;
		zmq_msg_init(&request);
		zmq_recv(responder, &request, 0);
		printf("Received Hello\n");
		zmq_msg_close(&request);
		
		// Do some 'work'
		imgData = MergeChars(mat1, mat2);

		// Send reply back to client
		zmq_msg_t reply;
		zmq_msg_init_size(&reply, IMG_WIDTH*IMG_HEIGHT*3*2);
		memcpy(zmq_msg_data(&reply), imgData, IMG_WIDTH*IMG_HEIGHT*3*2);
		zmq_send(responder, &reply, 0);
		zmq_msg_close(&reply);
	
	}
}

unsigned char * Communication::MergeChars(unsigned char *mat1, unsigned char *mat2)
{
	unsigned char *mergeMat = (unsigned char *)malloc(IMG_WIDTH*IMG_HEIGHT*3*2);
	long int i;
	for(i=0; i<IMG_WIDTH*IMG_HEIGHT*3; i++) {
		mergeMat[i] = mat1[i];
		mergeMat[i+IMG_WIDTH*IMG_HEIGHT*3] = mat2[i];
	}
	
	return mergeMat;
}
