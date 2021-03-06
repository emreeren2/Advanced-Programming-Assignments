#include<iostream>
#include<string>
#include<random> 
#include<time.h>
#include<thread>
#include<mutex>
#include<chrono> 
#include<iomanip>
#include<ctime>
#include"HW8DynIntQueue.h"

using namespace std;


mutex myMutex, coutMutex;
HW8DynIntQueue queue;
int total_customer_count;
int cashier2_treshold;
int min_arrival, max_arrival;
int min_checkout_time, max_checkout_time;
int TRANSACTION = 0; // this variable is incremented when cashier functions dequeue an item from queue
					 // therefore, we are able to count how many customer are transacted in total

// generating random number based on taken min/max parameter as an interval
int random_range(const int & min, const int & max) {  
	static mt19937 generator(time(0));   
	uniform_int_distribution<int> distribution(min, max);    
	return distribution(generator); 
}

// this function was taken and modified from "ProducerConsumer.cpp"
void customer()
{
	for(int i = 1; i <= total_customer_count; i++)
	{
		myMutex.lock();
		if (queue.getCurrentSize() != total_customer_count) 
		{  
			queue.enqueue(i);
			int size = queue.getCurrentSize(); // since we used size of queue in cout statemant, we should take it when mutex is lock and after the queue was updated 
			myMutex.unlock();				  	

			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 

			cout <<"New customer with ID  "<< i << "  has arrived (queue size is  "<< size << "): " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();

			int time = random_range(min_arrival, max_arrival);
			this_thread::sleep_for(chrono::seconds(time)); // sleeping customer thread based on random number "time" that is generated based on taken min/max parameter.
		}
		else
		{
			myMutex.unlock();
			i--;
		}	
	}
}

// this function was taken and modified from "ProducerConsumer.cpp"
void cashierFirst(int id)
{
	int time = random_range(min_checkout_time, max_checkout_time);
	this_thread::sleep_for(chrono::seconds(time));  // sleeping first cashier thread based on random number "time" that is generated based on taken min/max parameter.

	int item;
	while(TRANSACTION != total_customer_count) // if all customers did not be transacted, we will continue operation
	{
		myMutex.lock();
		if (!queue.isEmpty()) // if there is a customer that is not transacted in queue
		{  
			queue.dequeue(item); // we dequeue an item from queue, when mutex is lock
			int size = queue.getCurrentSize(); // since we used size of queue in cout statemant, we should take it when mutex is lock and after the queue was updated 
			TRANSACTION++; // we increase global variable TOTAL, which means that a customer is trasacted
			myMutex.unlock();

			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // we take current time in this section
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 

			cout << "Cashier " << id << " started transaction with customer " << item << " (queue size is " << size << "): " << put_time(ptm,"%X")<<endl;
			coutMutex.unlock();
			
			int time = random_range(min_checkout_time, max_checkout_time); 
			this_thread::sleep_for(chrono::seconds(time)); // sleeping customer thread based on random number "time" that is generated based on taken min/max parameter.

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // we take current time in this section
			localtime_s(ptm, &tt); 

			cout << "Cashier " << id << " finished transaction with customer " << item << " " << put_time(ptm,"%X")<<endl;
			coutMutex.unlock();
		}
		else
		{
			myMutex.unlock();
		}
	}
}

// this function was taken and modified from "ProducerConsumer.cpp"
void cashierSecond(int id) // almost same with "cashierFirst" function ---> different section has been written
{
	int time = random_range(min_checkout_time, max_checkout_time);
	this_thread::sleep_for(chrono::seconds(time)); 

	int item;
	while(TRANSACTION != total_customer_count)
	{
		myMutex.lock(); 
		if (!queue.isEmpty() && queue.getCurrentSize() >= cashier2_treshold) // since there is constraint in 2nd cashier, that is related with when it should work or should not work
		{																	 // 2nd cashier should be work only, when queue size is exceeded 2nd cashier's treshold
			queue.dequeue(item);
			int size = queue.getCurrentSize();
			TRANSACTION++;
			myMutex.unlock();

			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 

			cout << "Cashier " << id << " started transaction with customer " << item << " (queue size is " << size << "):" << put_time(ptm,"%X")<<endl;
			coutMutex.unlock();
			
			int time = random_range(min_checkout_time, max_checkout_time);
			this_thread::sleep_for(chrono::seconds(time));

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	
			localtime_s(ptm, &tt);  
			cout << "Cashier " << id << " finished transaction with customer " << item << " " <<  put_time(ptm,"%X")<<endl;
			coutMutex.unlock();
		}
		else
		{
			myMutex.unlock();
		}
	}
}

// this function is used for to display current time at the beggining of the program and at the end of the program
void currentTime(string str)
{
	time_t t1 = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm1 = new struct tm; 
	localtime_s(ptm1, &t1); 
	cout << str << put_time(ptm1,"%X")<<endl; 	
}


int main()
{
	cout << "Please enter the total number of customers: ";
	cin >> total_customer_count;

	cout << "Please enter the number of customers waiting in the queue to open the second cashier: ";
	cin >> cashier2_treshold;

	cout << "Please enter the inter-arrival time range between two customers: "<<endl;
	cout << "Min: "; cin >> min_arrival;
	cout << "Max: "; cin >> max_arrival;

	cout << "Please enter the checkout time range of cashiers: "<<endl;
	cout << "Min: "; cin >> min_checkout_time;
	cout << "Max: "; cin >> max_checkout_time;


	currentTime("Simulation starts: ");

	thread customers(customer);
	thread cashier1(cashierFirst, 1);
	thread cashier2(cashierSecond, 2);

	customers.join();
	cashier1.join();
	cashier2.join();

	currentTime("End of the simulation ends: ");

	return 0;
}
