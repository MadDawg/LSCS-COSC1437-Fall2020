#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> // std::sort, std::for_each
#include <numeric> // std::accumulate

using namespace std;

int main()
{
    cout << "The Test Scores program\n\n";

    cout << "Enter test scores from 0 to 100.\n"
        << "To end the program, enter -1.\n"
        << "Only the highest four scores are counted.\n\n";

    vector<int> scores;
    int score = 0;
    while (score != -1) {
        cout << "Enter score: ";
        cin >> score;

        // user really doesn't want to enter a score, so bail out
        if (cin.eof()){
            cin.clear();
            //cin.ignore(1000, '\n');
            score = -1;
        }
        else if (cin.fail()) {
            cin.clear();             // clear error bits
            cin.ignore(1000, '\n');  // discard input up to end of line
            cout << "Invalid number. Try again.\n";
        }
        else if (score > 100) {
            cout << "Score must be from 0 to 100. Try again.\n";
        }
        else if (score < -1) {
            cout << "Score can't be a negative number. Try again.\n";
        }
        else if (score > -1) {     // valid score, add to vector
            scores.push_back(score);
        }
    }

    if (scores.empty()) {                 // vector is empty
        cout << "\nNo scores entered.\n";
    }
    else if(scores.size() < 5){
        cout << "\nLess than 5 scores entered\n";
    }
    else {                                 // vector contains scores
        sort(scores.begin(), scores.end(), [](const int a, const int b){ // lambda function to configure std::sort
            return a > b;
        });

        // discard all but the first 4 scores
        // since the vector is sorted, we have the 4 highest scores
        scores.resize(4);

        cout << "\nHighest four scores: ";
        for_each(scores.begin(), scores.end(), [](const int score){ // another lambda function
            cout << score << ' ';
        });

        cout << "\nHighest score: " << scores[0]
            <<"\nLowest score: " << scores[scores.size()-1];

        // count perfect scores
        int perfects = 0;
        for (int score : scores){
            if (score == 100){ ++perfects; }
        }

        cout << "\nThis student has " << perfects << " perfect score(s)!\n";

        // calculate total of all scores
        int total = accumulate(scores.begin(), scores.end(), 0);

        // get the count and calculate the average
        auto score_count = scores.size();
        double average = static_cast<double>(total) / score_count;
        average = round(average * 10) / 10;

        // display the score count, total, and average
        cout << '\n'  // blank line
            << "Score count:   " << score_count << endl
            << "Score total:   " << total << endl
            << "Average score: " << average << endl << endl;
    }
}
