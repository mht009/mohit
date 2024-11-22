/*
 * Scientific Calculator Interface Definition
 */

program CALCULATOR_PROG {
    version CALCULATOR_VERS {
        double ADD(doublepair) = 1;
        double SUBTRACT(doublepair) = 2;
        double MULTIPLY(doublepair) = 3;
        double DIVIDE(doublepair) = 4;
        double SIN(double) = 5;
        double COS(double) = 6;
        double TAN(double) = 7;
        double LOG(double) = 8;
    } = 1;
} = 0x31234567;

struct doublepair {
    double a;
    double b;
};

