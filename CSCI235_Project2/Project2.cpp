/*
Jonathan Balina
CSCI 235
Pavel Shostak
*/

#include<iostream>
#include<vector>

using namespace std;


/*
This recursive function will return true once the new string is equal to the given key
It will accomplish this by using a for loop to add each element of the element vector one at a time,
then recursively calling itself whenever a combination works
It also adds the index to the answer vector whenever the function returns true.
*/
bool f(string res, const string key, const vector<string>& elements, vector<int>& answer)
{
    for(int i = 0; i < elements.size(); i++)
    {
        string temp = res + elements[i];
        if(temp == key)
        {
            answer.push_back(i);
            return true;
        }
        //boolean variable works to determine if this is a successful combination
        //a for loop checks if the letters of the current combination match the letters of the provided key and sets works to false otherwise
        bool works = true;
        for(int j = 0; j < temp.length(); j++)
        {
            if(temp[j] != key[j])
            {
                works = false;
            }
        }
        //if works is still true then the function will call itself
        //if the function after many iterations is true then the index of the correct combinations will be stored backwards into the answer vector
        if(works)
        {
            if(f(temp, key, elements, answer))
            {
                answer.push_back(i);
                return true;
            }
            else
            {
            }
        }
        else
        {
        }
    }
    return false;
}

//since the answers are placed into the vector backwards, a function is needed to reverse the order
void flip(vector<int>& answer)
{
    //fills a temporary vector with the contents of answer starting from the end
    vector<int> temp;
    for(int i = answer.size()-1; i >= 0 ; i--)
    {
    temp.push_back(answer[i]);
    }
    //sets answer to equal temp
    answer = temp;
}

//UI to ask for inputs
main()
{
    string key;
    cout << "Enter target string:";
    cin >> key;
    cout << "Enter amount of elements:";
    int amount;
    cin >> amount;
    vector<string> elements;
    vector<int> answer;
    cout << "Enter elements:" << endl;
    for(int i = 0; i < amount; i++)
    {
        cout << "Element #" << i+1 << ": ";
        string input;
        cin >> input;
        elements.push_back(input);
    }
    f("", key, elements, answer);
    flip(answer);
    cout << "Your answer is:" << endl;
    for(int i = 0; i < answer.size(); i++)
    {

        cout << answer[i] << " ";
    }
    cout << endl;
    if(answer.size() == 0)
    {
        cout << "No answer found" << endl;
    }

}
