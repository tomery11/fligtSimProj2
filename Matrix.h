//
// Created by tomer on 1/13/19.
//

#ifndef FLIGTSIMPROJ2_MATRIX_H
#define FLIGTSIMPROJ2_MATRIX_H


#include "ISearchable.h"
using namespace std;


class Node{
public:
    int i;
    int j;

    Node(int x, int y){
        this->i=x;
        this->j=y;
    }

    bool operator==(Node& rhs){
        bool ans= (rhs.i==i && rhs.j==j);
        return ans;
    }
};


class Matrix : public ISearchable<Node>{
private:
    int **matrix;
    int row;
    int col;
    Node* start;
    Node*  goal;


public:
    // we get here a specified starting node and goal node
    Matrix(int **matrix, int row, int col, Node* start, Node* goal);
    // we get here a specified starting point and starting goal by int
    Matrix(int **matrix, int row, int col, int i_start, int j_start, int i_goal, int j_goal);
    //there aren't any starting points and goals
    Matrix(int **matrix, int row, int col);


    State<Node>* stateGenarator(int i, int j, State<Node>* pre);

    State<Node>* getInitialState() override;
    set<State<Node>*> getAllPossibleStates(State<Node>* currState) override;
    bool isGoal(State<Node>* currState) override;






    ~Matrix() ;



};


Matrix::Matrix(int **matrix, int row, int col, Node *start, Node *goal) {
    this->matrix=matrix;
    this->row=row;
    this->col=col;
    this->start=start;
    this->goal=goal;
}

Matrix::Matrix(int **matrix, int row, int col, int i_start, int j_start, int i_goal, int j_goal) {
    this->matrix=matrix;
    this->row=row;
    this->col=col;
    start= new Node(i_start,j_start);
    goal= new Node(i_goal,j_goal);
}

Matrix::Matrix(int **matrix, int row, int col) {
    this->matrix=matrix;
    this->row=row;
    this->col=col;
    start = new Node(0,0);
    goal = new Node (row-1,col-1);
}

State<Node> *Matrix::stateGenarator(int i, int j, State<Node> *pre) {
    //first of all we check if there is an edge
    if(matrix[i][j]==-1){
        return nullptr;
    }
    Node *myNode= new Node(i,j);
    double weight;
    //double pre_weight=0;
    if(pre== nullptr){
        weight= matrix[i][j];
    }
    else{
        weight= pre->getWeight() + matrix[i][j];
    }
    State<Node>* ans= new State<Node>(myNode,weight,pre);
    return ans;
}

Matrix::~Matrix() {
    delete (start);
    delete (goal);
}

State<Node> *Matrix::getInitialState() {
    return stateGenarator(start->i,start->j, nullptr);
}

set<State<Node> *> Matrix::getAllPossibleStates(State<Node>* currState) {
    //current state
    Node *location= currState->getState();
    int i= location->i;
    int j= location->j;
    //node that will be inserted to set
    State<Node>* insert_toSet;
    //this is the set that will be returned with all possible states
    set<State<Node>*> toReturn;
    if(i!=row-1){
        insert_toSet = stateGenarator(i+1,j,currState);
        if(insert_toSet != nullptr)
            toReturn.insert(insert_toSet);
    }
    if(j!=col-1){
        insert_toSet = stateGenarator(i, j+1, currState);
        if(insert_toSet != nullptr)
            toReturn.insert(insert_toSet);
    }
    if(i!=0){
        insert_toSet = stateGenarator(i-1, j, currState);
        if(insert_toSet != nullptr)
            toReturn.insert(insert_toSet);
    }
    if(j!=0){
        insert_toSet=(i,j-1,currState);
        if(insert_toSet != nullptr)
            toReturn.insert(insert_toSet);
    }
    return toReturn;







}

bool Matrix::isGoal(State<Node>* currState) {
    bool ans= false;
    //get current state
    Node *location= currState->getState();
    if(*location == *goal)
        ans=true;
    return ans;
}


#endif //FLIGTSIMPROJ2_MATRIX_H
