typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;

#define MSGSIZE 8
// A structure to represent a queue
struct Queue
{
    int front, rear, size;
    unsigned capacity;
    int* array;
};
int GetMessageBuffer(void);
void FreeMessageBuffer(int msg_number);

struct Queue* m_queue(unsigned capacity);

// Queue is full when size becomes equal to the capacity
int isFull(struct Queue* queue);

// Queue is empty when size is 0
int isEmpty(struct Queue* queue);

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, int item);

// Function to remove an item from queue.
// It changes front and size
int dequeue(struct Queue* queue);

// Function to get front of queue
int front(struct Queue* queue);

// Function to get rear of queue
int rear(struct Queue* queue);

void intitialize_queues(void);
