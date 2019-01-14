#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"

#define TMR_PERIOD         500000U
#if defined(TWR_KV46F150M)
#define LPTMR0_IDX LPTMR_IDX
#endif

void lptmr_call_back(void) {
    // Toggle LED1
	LED1_TOGGLE;
}

typedef struct node {
  int data;
  struct node *next;
} Node;

typedef struct Queue {
  Node *head;
  Node *tail;
} Queue;

Queue* InitBuf() {
  Queue* queue = (Queue *) malloc(sizeof(Queue));
  queue->head = NULL;
  queue->tail = NULL;
  return queue;
}

void AddBuf(Queue* queue, int value) {
  Node* node = (Node *) malloc(sizeof(Node));
  node->data = value;
  node->next = NULL;
  if (queue->tail == NULL) {
    queue->head = node;
  } else {
    queue->tail->next = node;
  }
  queue->tail = node;
}

void RemoveBuf(Queue* queue) {
  if (queue->head == NULL) {
    return;
  }
  Node* head = queue->head;
  queue->head = queue->head->next;
  free(head);
}

void FreeBuf(Queue* queue) {
	while(queue->head != NULL) {
		Node *head = queue->head;
		queue->head = queue->head->next;
		free(head);
	}
	free(queue);
}

int main (void) {
    // LPTMR configurations
    lptmr_user_config_t lptmrConfig =
    {
        .timerMode = kLptmrTimerModeTimeCounter,
        .freeRunningEnable = false,
        .prescalerEnable = true,
        .prescalerClockSource = kClockLptmrSrcLpoClk,
        .prescalerValue = kLptmrPrescalerDivide2,
        .isInterruptEnabled = true,
    };
    // LPTMR driver state information
    lptmr_state_t lptmrState;

    // Initialize standard SDK demo application pins
    hardware_init();

    // Initialize LPTMR
    LPTMR_DRV_Init(LPTMR0_IDX, &lptmrState, &lptmrConfig);
    // Set timer period for TMR_PERIOD seconds
    LPTMR_DRV_SetTimerPeriodUs(LPTMR0_IDX, TMR_PERIOD);
    // Install interrupt call back function for LPTMR
    LPTMR_DRV_InstallCallback(LPTMR0_IDX, lptmr_call_back);
    // Start LPTMR
    LPTMR_DRV_Start(LPTMR0_IDX);

    // Initialize LED1
    LED1_EN;

    PRINTF("\n\rMy Test Application!\n");
    Queue* queue = InitBuf();
    AddBuf(queue, 5);
    PRINTF("\r5 -> %i\n", queue->head->data);

    AddBuf(queue, 6);
    AddBuf(queue, 7);
    PRINTF("\r5 -> %i\n", queue->head->data);
    RemoveBuf(queue);
    PRINTF("\r6 -> %i\n", queue->head->data);

    RemoveBuf(queue);
    RemoveBuf(queue);

    PRINTF("\rNULL -> %i\n", queue->head);
    FreeBuf(queue);
    return 0;
}
