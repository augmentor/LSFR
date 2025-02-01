// LFSR.cpp : This file contains the implementation of the LFSR state estimator
// The code below represents adaptation of the matrix method
// found in the article by Jason Sachs found here
// https://www.embeddedrelated.com/showarticle/1114.php
// Great introduction to the theory about LFSR was learned from this video lessons from Tanja Lange
// https://www.youtube.com/watch?v=rZ3w1yldLSw&t=126s
// https://www.youtube.com/watch?v=n8zM_9bpaks&t=1048s

#include "LFSR.h"
#include <vector>

using namespace std;

// binary Matrix-Vector multiplication
template<uint32_t N>
vector<uint8_t> MatrixVectorProduct(const vector<vector<uint8_t>>& iMatrix, const vector<uint8_t>& iVector) 
{
    vector<uint8_t> prod(N, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            prod[i] ^= (iMatrix[i][j] & iVector[j]);
        }
    }
    return prod;
}

// binary Matrix-Matrix multiplication
template<uint32_t N>
vector<vector<uint8_t>> MatrixMatrixProduct(const vector<vector<uint8_t>>& iMatrixA, const vector<vector<uint8_t>>& iMatrixB)
{
    vector<vector<uint8_t>> prod(N, vector<uint8_t>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                prod[i][j] ^= (iMatrixA[i][k] & iMatrixB[k][j]);
    return prod;
}

// method produces binary raised matrice to given exponent  
template<uint32_t N>
vector<vector<uint8_t>> MatrixFactor(vector<vector<uint8_t>> iMatrix, uint64_t iExponent)
{
    vector<vector<uint8_t>> factor(N, vector<uint8_t>(N, 0));
    for (int i = 0; i < N; i++) factor[i][i] = 1;

    while (iExponent) 
    {
        if (iExponent & 1) factor = MatrixMatrixProduct<N>(factor, iMatrix);
        iMatrix = MatrixMatrixProduct<N>(iMatrix, iMatrix);
        iExponent >>= 1;
    }
    return factor;
}

// method returns the state of the LFSR generator on arbitrary step
template<uint32_t N>
uint64_t GetLFSRState(uint64_t iSeed, uint64_t iPolynomial, uint64_t iStep) 
{
    vector<vector<uint8_t>> LFSRMatrix(N, vector<uint8_t>(N, 0));
    // create LFSR transition matrix identity part
    for (int i = 1; i < N; i++) 
    {
        LFSRMatrix[i-1][i] = 1;
    }
    // insert generator polinomial
    for (int i = 0; i < N; i++) 
    {
        if (iPolynomial & (1ULL << i)) LFSRMatrix[N - 1][N-i-1] = 1;
    }

    //factorisation of the matrix to the k-th range
    vector<vector<uint8_t>> FactorMatrix = MatrixFactor<N>(LFSRMatrix, iStep);

    //prep initial vector state
    vector<uint8_t> State(N, 0);
    for (int i = 0; i < N; i++) 
    {
        State[i] = (iSeed >> i) & 1;
    }

    // state after k steps
    vector<uint8_t> ShiftedState = MatrixVectorProduct<N>(FactorMatrix, State);

    //back convertion
    uint64_t result = 0;
    for (int i = 0; i < N; i++) 
    {
        result |= ((1ULL & ShiftedState[N-i-1]) << i);
    }
    return result;
}

// TARGET FUNCTION
uint64_t rfsr42(uint64_t shift, uint64_t initial_state)
{
    const uint64_t polynomial = 0b1100000101010001110011011110000010011101111;
    return GetLFSRState<42>(initial_state, polynomial, shift);
}

//Small generator TARGET FUNCTION
uint64_t rfsr4(uint64_t shift, uint64_t initial_state)
{
    const uint64_t polynomial = 0b11001; // X^4+X^3+1
    return GetLFSRState<4>(initial_state, polynomial, shift);
}