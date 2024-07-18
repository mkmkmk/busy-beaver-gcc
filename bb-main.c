#include <stdio.h>

#if 0
#define STATE_N (4)
#define SYMBOL_N (2)
#define TAPE_N (16)

int move_tb[SYMBOL_N][STATE_N] =
    {
        { +1, -1, +1, +1 },
        { -1, -1, -1, +1 }
    };

int state_tb[SYMBOL_N][STATE_N] =
    {
        { 1, 0, -1, 3 },
        { 1, 2,  3, 0 }
    };

int write_tb[SYMBOL_N][STATE_N] =
    {
        { 1, 1, 1, 1 },
        { 1, 0, 1, 0 }
    };


#elif 0
// https://bbchallenge.org/1RB1RA_0LC1LE_1LD1LC_1LA0LB_1LF1RE_---0RA
#define STATE_N (6)
#define SYMBOL_N (2)
#define TAPE_N (8000)

int write_tb[SYMBOL_N][STATE_N] =
    {
        { 1, 0, 1, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 0,}
    };


int move_tb[SYMBOL_N][STATE_N] =
    {
        {+1,-1,-1,-1,-1,-1},
        {+1,-1,-1,-1,+1,+1},
    };


int state_tb[SYMBOL_N][STATE_N] =
    {
       {1,2,3,0,5,-1},
       {0,4,2,1,4,0}
    };

#elif 1

// https://bbchallenge.org/1RB1LC_1RC1RB_1RD0LE_1LA1LD_1RZ0LA
// https://wiki.bbchallenge.org/wiki/5-state_busy_beaver_winner

#define STATE_N (5)
#define SYMBOL_N (2)
#define TAPE_N (24500)

// 11_11_10_11_10
int write_tb[SYMBOL_N][STATE_N] =
    {
        { 1, 1, 1, 1, 1, },
        { 1, 1, 0, 1, 0, }
    };

// RL_RR_RL_LL_RL
// +-_++_+-_--_+-
int move_tb[SYMBOL_N][STATE_N] =
    {
        {+1,+1,+1,-1,+1},
        {-1,+1,-1,-1,-1},
    };

// BC_CB_DE_AD_ZA
// 12_21_34_03_Z0
int state_tb[SYMBOL_N][STATE_N] =
    {
       {1,2,3,0,-1},
       {2,1,4,3, 0}
    };

#endif



int tape[TAPE_N];

int main(void)
{
    int header = TAPE_N / 2;
    int state = 0;
    int step = 0;

    while (1)
    {

        // if (state < 0 || step < 1000 || (step % 1000000) == 0)

        // https://arxiv.org/pdf/0906.3749
        // 5-state BB winer readouts
        // "Let C(n) = ...0(A0)1n0..."
        if (state == 0 || state < 0)
        {
            int s = 0;
            int ss = 0;
            int mss = 0;
            int one = 0;
            int sel = 0;
            for (int i = 0; i < TAPE_N; ++i)
            {
                s += tape[i];
                if (tape[i]) ss++; else ss = 0;
                if (mss<ss) mss = ss;
                if (one == 0 && tape[i]) one = 1;
                if (i == header && !one && i < TAPE_N-2 && tape[i+1]) sel = 1;
            }
            if (state < 0 || step == 0 || (mss == s && sel))
            {
                printf("%10d: ", step);
                printf(" (%5d,%5d, %c) ", s, mss, "hABCDEFGHIJ"[1 + state]);
                for (int i = 0; i < TAPE_N; ++i)
                    printf("%c%c ", i == header ? "hABCDEFGHIJ"[1 + state] : ' ', "_1"[tape[i]]);
                printf("\n");
            }
        }

        if (state == -1)
        {
            printf("\n halt\n");
            break;
        }

        int read = tape[header];
        tape[header] = write_tb[read][state];
        header += move_tb[read][state];
        state = state_tb[read][state];

        if (header == -1 || header == TAPE_N)
        {
            printf("\nERROR: out of tape (header=%d)\n", header);
            break;
        }

        if (state < -1 || state >= STATE_N)
        {
            printf("\nERROR: state: %d\n", state);
            break;
        }

        step++;
    }
    printf("\n steps: %d \n", step);
    printf("\n DONE\n");
    return 0;
}

