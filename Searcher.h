//
// Created by tomer on 1/12/19.
//

#ifndef FLIGTSIMPROJ2_SEARCHER_H
#define FLIGTSIMPROJ2_SEARCHER_H

#include "ISearcher.h"
#include "CompareState.h"
#include "State.h"
#include "Matrix.h"
#include <queue>


template <class T>
class Searcher : public ISearcher {
protected:
    set<State<T>*> done;
    int nodesEvaluated=0;
    ISearchable<T>* curr_Searchable;

public:
    Searcher<T> () = default;
    virtual void clearAllStates()=0;
    virtual State<T>* popOpenList()=0;
    virtual void addToOpenList(State<T>* state)=0;

    virtual bool isOpenListEmpty()=0;

    string from_string_toSolution(State<Node>* curr_state);




    void initMembers(ISearchable<T>& searchable);
    void saveToPath(State<T>* goal);
    string search(ISearchable<T>& searchable) override;
    bool has_visited(State<T>* state);
    void visit(State<T>* state);
    int getNumberOfNodesEvaluated() override;
};

template<class T>
void Searcher<T>::visit(State<T> *state) {
    done.insert(state);
}

template<class T>
bool Searcher<T>::has_visited(State<T> *state) {
    set<string>::iterator ptr ;
    for(ptr= done.begin();ptr!=done.end(); *ptr++){
        if(ptr==PointerStateCompare<T>(state))
            return true;
    }
    return false;
}

template<class T>
int Searcher<T>::getNumberOfNodesEvaluated() {
    return nodesEvaluated;
}

template<class T>
void Searcher<T>::initMembers(ISearchable<T> &searchable) {
    nodesEvaluated= 0;
    curr_Searchable = &searchable;
}

template<class T>
void Searcher<T>::saveToPath(State<T> *goal) {
    State<T>* vertex = goal;
    do{
        vertex->switchSolution();
        vertex = vertex->getPre();
    }while(vertex!= nullptr);
}

template<class T>
string Searcher<T>::search(ISearchable<T> &searchable) {

    initMembers(searchable);

    addToOpenList(searchable.getInitialState());
    //as long as not taken care of evaluated nodes
    while(!isOpenListEmpty()){
        State<T>* node = popOpenList();
        if(searchable.isGoal(node)){

            saveToPath(node);

            clearAllStates();
            return from_string_toSolution(node);
        }
        //if not reached to goal state
        set<State<T>*> toBeCompleted = searchable.getAllPossibleStates(node);

        visit(node);

        if(node->getWeight()==-1){
            continue;
        }
        for(auto son : toBeCompleted){
            if(!has_visited(son)){
                addToOpenList(son);
            }
        }
    }
    //case if didn't find any solution
    return nullptr;
}

template<class T>
string Searcher<T>::from_string_toSolution(State<Node>* curr_state) {



    string toReturn;

    string up = "Up, ";
    string down = "Down, ";
    string right = "Right, ";
    string left = "Left, ";


    State<Node>* curr= curr_state;
    Node* my_state;
    State<Node>* previous= curr_state->getPre();
    Node* previous_state;

    while(previous != nullptr){
        previous_state=previous->getState();
        my_state=curr->getState();

        if((previous_state->i>my_state->i) && (previous_state->j==my_state->j)){
            toReturn.insert(0,up);
        }

        else if((previous_state->i<my_state->i) && (previous_state->j==my_state->j)){
            toReturn.insert(0,down);
        }

        else if((previous_state->i==my_state->i)&&(previous_state->j<my_state->j)){
            toReturn.insert(0,right);
        }
        else if((previous_state->i==my_state->i) && (previous_state->j<my_state->j)){
            toReturn.insert(0,left);
        }

        curr=previous;
        previous=previous->getPre();



    }

    toReturn.pop_back();
    return toReturn;



}


#endif //FLIGTSIMPROJ2_SEARCHER_H
