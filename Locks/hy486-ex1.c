#define cartReady = 0;
#define startTour = 1;

shared int state = cartReady;		//keeping the state for the cart
shared boolean pass = false;		/*true when a passenger come and 
										it's ready to join an cart*/
shared boolean cart = false;		/*true when a cart came and 
										it's rdy to carry a passenger*/

CLH_Lock currPassenger;				//CLH lock starvation-free
CLH_Lock currCart;					//CLH lock starvation-free

void passenger(){
	walk_around();					//do something before take the cart
	
	lock(currPassenger);			//try to lock, waiting until it's our state
	while(cart == false) noop;		//wait for cart 
	pass = true;					//declare passenger purpose
	while(state != startTour) noop; //spinning until the cart change on startTour
	pass = false;					//declare that we dont need any more cart
	unlock(currPassenger);			//i am get a cart, give order on next passenger

	buy_something_from_shop();		//do something
}

void cart(){

	lock(currCart);				/*try to lock, the first cart that lock 
									will take the first passenger*/
	state = cartReady;			//declare the current state
	cart = true;				//declare our purpose
	while(pass == false) noop;  //waiting passenger to come
	cart = false;				//declare that our cart take by someone
	state = startTour;			//change state on startTour
	while(pass == true) noop;	//wait the passenger to join us
	unlock(currCart);			//leaving critical region
	
	start_tour();				//start the tour
}