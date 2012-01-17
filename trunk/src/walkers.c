
void downRed(long int d){
	if(pic[d].red > 0){
		pic[d].red -= 1;
	}
}

void upRed(long int d){
	if(pic[d].red < 255){
		pic[d].red += 1;
	}
}


void upGreen(long int d){
	if(pic[d].green < 255){
		pic[d].green += 1;
	}
}

void downGreen(long int d){
	if(pic[d].green > 0){
		pic[d].green -= 1;
	}
}

void downBlue(long int d){
	if(pic[d].blue > 0){
		pic[d].blue -= 1;
	}
}

void upBlue(long int d){
	if(pic[d].blue < 255){
		pic[d].blue += 1;
	}
}




void init_walker(){
	walkers = { 	{ (rand()%size), &downRed },
	 							 	{ (rand()%size), &upRed },
									{ (rand()%size), &downGreen },
									{ (rand()%size), &upGreen },
									{ (rand()%size), &downBlue },
									{ (rand()%size), &upBlue }	
								};
} 
