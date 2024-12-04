#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <unordered_map>
using namespace std;

class IObserver {
public:
    virtual void update(int version) = 0;
};

class Amazing {
public:
    void addObserver(IObserver* ob) {
        cout << "Observer is added\n";
        observers.push_back(ob);
    }

    void removeObserver(IObserver* ob) {
        observers.erase(std::remove(observers.begin(), observers.end(), ob), observers.end());
        cout << "Observer is removed\n";
    }

    void notifyObserver(){
        for (auto it : observers) {
            it->update(version_);
        }
    }

    void update(int version) {
        version_ = version;
        notifyObserver();
    }

private:
    std::vector<IObserver*> observers;
    int version_ = 0;
};

class School : public IObserver {
public:
    void update(int version) {
        cout << "School updates amazing to version " << version << endl;
    }
};

class Hospital : public IObserver {
public:
    void update(int version) {
        cout << "Hospital updates amazing to version " << version << endl;
    }
};


bool isPalindrome(string str) {
    str.erase(remove_if(str.begin(), str.end(), [](char c) {
        return !isalpha(c);
        }), str.end());

    transform(str.begin(), str.end(), str.begin(), ::tolower);

    string reversed_str = str;
    reverse(reversed_str.begin(), reversed_str.end());

    return str == reversed_str;
}

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> result;
    std::unordered_map<int, int> temp;
    for (int i = 0; i < nums.size(); ++i) {
        int value = target - nums[i];
        if (temp.find(value) != temp.end()) {
            result.push_back(i);
            result.push_back(temp[value]);
        }
        else {
            temp.emplace(nums[i], i);
        }
    }
    return result;
}

int main() {
    School* school = new School();
    Hospital* hospital = new Hospital();

    Amazing amazing;
    amazing.addObserver(school);

    amazing.update(1);

    amazing.addObserver(hospital);
    amazing.update(2);

    amazing.removeObserver(school);

    amazing.update(3);



	return 0;
}