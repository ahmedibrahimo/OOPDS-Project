// Antares TT6L
// Member 1: Rashid Hassan Abdalla – 251UC250GF
// Member 2: Mohamed Yassir Mohamed – 251UC25026
// Member 3: Ahmed Ibrahim Mohamed – 251UC2519U
// Member 4: Jeremy Puah – 252UC253W6

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <queue>


using namespace std;

void trimCR(string& s) { //remove carriage return if present, for linux
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
}

bool didHit(double hitChance) {
    double roll = rand() % 100;  // 0–99
    return roll < hitChance;
}

class Ship;

Ship* getRandomEnemy(vector<Ship*>& enemies) {
    if (enemies.empty()) return nullptr;
    int index = rand() % enemies.size();
    return enemies[index];
}

//
// CLASS CREATION STARTS
//

class CrewMember {
private:
    string id;
    string name;
    string role; // pilot, gunner, torpedo_handler

public:
    CrewMember(string id, const string& name, const string& role)
        : id(id), name(name), role(role) {}

    string getRole() const {
        return role;
    }

    string getName() const {
        return name;
    }
};

class Weapon {
private:
    string type;   // "light_cannon" or "torpedo"
    int power;
    CrewMember* crew;

public:
    Weapon(const string& type, int power, CrewMember* crew)
        : type(type), power(power), crew(crew) {}

    int getPower() const {
        return power;
    }

    string getType() const {
        return type;
    }

    CrewMember* getCrew() const {
        return crew;
    }
};

Weapon* getLightCannon(const vector<Weapon*>& weapons) {
    for (Weapon* w : weapons) {
        if (w->getType() == "Light Cannon")
            return w;
    }
    return nullptr;
}

Weapon* getTorpedo(const vector<Weapon*>& weapons) {
    for (Weapon* w : weapons) {
        if (w->getType() == "Torpedo")
            return w;
    }
    return nullptr;
}


class Ship {
protected:
    string id;
    string name;
    string shipType;
    int maxHitPoints;
    int hitPoints;
    int hitChance;
    int maxPilot;
    int maxCannon;
    int maxTorpedo;
    vector<CrewMember*> crew;
    vector<CrewMember*> pilot;
    vector<Weapon*> weapons;
    

public:
    Ship(const string& id, const string& name, int hp, int hitChance, const int maxPilot, const int maxCannon, const int maxTorpedo)
    : id(id), name(name), maxHitPoints(hp), hitPoints(hp), hitChance(hitChance), maxPilot(maxPilot), maxCannon(maxCannon), maxTorpedo(maxTorpedo){}

    virtual ~Ship() {}

    virtual void attack(vector<Ship*>& enemies) = 0; // abstract

    bool operator<(const Ship& other) const { 
    return hitPoints < other.hitPoints;
    }

    string getShipType() const {
        return shipType;
    }

    void takeDamage(int dmg) {
        hitPoints -= dmg;
    }

    bool isDestroyed() const {
        return hitPoints <= 0;
    }

    string getName() const {
        return name;
    }

    double getHitChance() const {
        if (maxPilot > getPilotCount()){
            return 100 - ((100 - hitChance) * 0.75);
        }
        return hitChance;
    }

    int getMaxPilot() const {
        return maxPilot;
    }

    int getMaxCannon() const{
        return maxCannon;
    }

    int getMaxTorpedo() const{
        return maxTorpedo;
    }

    int getPilotCount() const {
        return pilot.size();;
    }

    int getHitPoints() const {
        return hitPoints;
    }

    int getMaxHitPoints() const {
        return maxHitPoints;
    }

    string getID() const {
        return id;
    }

    void addCrew(CrewMember* c) {
        crew.push_back(c);
    }

    void addPilot(CrewMember* c){
        pilot.push_back(c);
    }

    void addWeapon(Weapon* w) {
        weapons.push_back(w);
    }

    virtual void printDetails(){
        cout << "[" << id << "] " << "  " << name << "  " << "(" << shipType << ")\n";
        cout << "   HP: " << hitPoints << "/" << maxHitPoints << "\n";
        cout << "   Pilots (" << pilot.size() << "/" << maxPilot << "): ";
        bool first = true;
        for (CrewMember* p : pilot){
            if (!first) {
            cout << ", ";
            }
            cout << p->getName();
            first = false;
        }
        cout << "\n";
        cout << "   Gunners (" << weapons.size() << "/" << maxCannon << "): ";
        first = true;
        for (Weapon* w : weapons){
            if (!first) {
            cout << ", ";
            }
            cout << w->getCrew()->getName();
            first = false;
        }
        cout << "\n";
    }
};

class Guerriero : public Ship {

private:

public:
    Guerriero(const string& id, const string& name)
        : Ship(id, name, 123, 26, 1, 1, 0) {
        shipType = "Guerriero";
        }

    void attack(vector<Ship*>& enemies) override {
        Ship* target = getRandomEnemy(enemies);
        if (!target) return;

        Weapon* cannon = getLightCannon(weapons);
        if (!cannon && !weapons.empty()) {
            cannon = weapons[0];
        }
        if (!cannon) return;

        if (didHit(this->getHitChance())) {
            int damage = cannon->getPower();
            target->takeDamage(damage);

            cout << shipType << " " << name << " hits " << target->getShipType() << " " << target->getName()
                 << " with " << cannon->getType() << " for " << damage << " damage\n";
        } else {
            cout << shipType << " " << name << " misses " << target->getShipType() << " " << target->getName() << " With " << cannon->getType() << endl;
        }
    }

    void setPilotasGunner(){
        this->addWeapon(new Weapon("Light Cannon", 96, pilot.back()));
    }

    void printDetails() override{
        cout << "[" << id << "] " << "  " << name << "  " << "(" << shipType << ")\n";
        cout << "   HP: " << hitPoints << "/" << maxHitPoints << "\n";
        cout << "   Pilots (" << pilot.size() << "/" << maxPilot << "): ";
        bool first = true;
        for (CrewMember* p : pilot){
            if (!first) {
            cout << ", ";
            }
            cout << p->getName();
            first = false;
        }
        cout << "\n";
        cout << "   Gunners (" << weapons.size() << "/" << maxCannon << "): ";
        first = true;
        for (Weapon* w : weapons){
            if (!first) {
            cout << ", ";
            }
            cout << w->getCrew()->getName();
            first = false;
        }
        cout << "\n";
    }
};

class Medio : public Ship {
public:
    Medio(const string& id, const string& name)
        : Ship(id, name, 214, 31, 1, 2, 0) {
        shipType = "Medio";
        }

    void attack(vector<Ship*>& enemies) override {
        for (Weapon* w : weapons){
            Ship* target = getRandomEnemy(enemies);
            if (!target) return;
            
            if (didHit(this->getHitChance())) {
                int damage = w->getPower();
                target->takeDamage(damage);

                cout << shipType << " " << name << " hits " << target->getShipType() << " " << target->getName()
                     << " with " << w->getType() << " for " << damage << " damage\n";
            } else {
                cout << shipType << " " << name << " misses " << target->getShipType() << " " << target->getName() << " With " << w->getType() << endl;
            }
        }
    }
};

class Corazzata : public Ship {
public:
    Corazzata(const string& id, const string& name)
        : Ship(id, name, 1031, 50, 2, 10, 4) {
        shipType = "Corazzata";
        }

    int findTorpedoCount() const {
        int count = 0;
        for (Weapon* w : weapons) {
            if (w->getType() == "Torpedo") {
                count++;
            }
        }
        return count;
    }

    int findGunnerCount() const {
        int count = 0;
        for (Weapon* w : weapons) {
            if (w->getType() == "Light Cannon") {
                count++;
            }
        }
        return count;
    }

    void attack(vector<Ship*>& enemies) override {
        for (Weapon* w : weapons){
            Ship* target = getRandomEnemy(enemies);
            if (!target) return;

            if (didHit(this->getHitChance())) {
                int damage = w->getPower();
                target->takeDamage(damage);

                cout << shipType << " " << name << " hits " << target->getShipType() << " " << target->getName()
                     << " with " << w->getType() << " for " << damage << " damage\n";
            } else {
                cout << shipType << " " << name << " misses " << target->getShipType() << " " << target->getName() << " With " << w->getType() << endl;
            }
        }
    }

    void printDetails() override{
        cout << "[" << id << "] " << "  " << name << "  " << "(" << shipType << ")\n";
        cout << "   HP: " << hitPoints << "/" << maxHitPoints << "\n";
        cout << "   Pilots (" << pilot.size() << "/" << maxPilot << "):";
        bool first = true;
        for (CrewMember* p : pilot){
            if (!first) {
            cout << ", ";
            }
            cout << " " << p->getName();
            first = false;
        }
        cout << "\n";
        cout << "   Gunners (" << findGunnerCount() << "/" << maxCannon << "): ";
        first = true;
        for (Weapon* w : weapons){
            if (w->getType() == "Torpedo"){
                continue;
            }
            if (!first) {
            cout << ", ";
            }
            cout << w->getCrew()->getName();
            first = false;
        }
        cout << "\n";
        cout << "   Torp Handlers (" << findTorpedoCount() << "/" << maxTorpedo << "): ";
        first = true;
        for (Weapon* w : weapons){
            if (w->getType() == "Light Cannon"){
                continue;
            }
            if (!first) {
            cout << ", ";
            }
            cout << w->getCrew()->getName();
            first = false;
        }
        cout << "\n";
    
    }
};

class Jager : public Ship {
public:
    Jager(const string& id, const string& name)
        : Ship(id, name, 112, 24, 1, 1, 0) {
        shipType = "Jager";
        }

    void attack(vector<Ship*>& enemies) override {
        Ship* target = getRandomEnemy(enemies);
        if (!target) return;

        Weapon* cannon = getLightCannon(weapons);
        if (!cannon && !weapons.empty()) {
            cannon = weapons[0];
        }
        if (!cannon) return;

        if (didHit(this->getHitChance())) {
            int damage = cannon->getPower();
            target->takeDamage(damage);

            cout << shipType << " " << name << " hits " << target->getShipType() << " " << target->getName()
                 << " with " << cannon->getType() << " for " << damage << " damage\n";
        } else {
            cout << shipType << " " << name << " misses " << target->getShipType() << " " << target->getName() << " With " << cannon->getType() << endl;
        }
    }

    void setPilotasGunner(){
        this->addWeapon(new Weapon("Light Cannon", 96, pilot.back()));
    }
};

class Kreuzer : public Ship {
public:
    Kreuzer(const string& id, const string& name)
        : Ship(id, name, 212, 29, 1, 2, 0) {
        shipType = "Kreuzer";
        }

    void attack(vector<Ship*>& enemies) override {
        for (Weapon* w : weapons){
            Ship* target = getRandomEnemy(enemies);
            if (!target) return;

            if (didHit(this->getHitChance())) {
                int damage = w->getPower();
                target->takeDamage(damage);

                cout << shipType << " " << name << " hits " << target->getShipType() << " " << target->getName()
                     << " with " << w->getType() << " for " << damage << " damage\n";
            } else {
                cout << shipType << " " << name << " misses " << target->getShipType() << " " << target->getName() << " With " << w->getType() << endl;
            }
        }   
    }
};

class Fregatte : public Ship {
public:
    Fregatte(const string& id, const string& name)
        : Ship(id, name, 1143, 60, 2, 11, 5) {
        shipType = "Fregatte";
        }

    int findTorpedoCount() const {
        int count = 0;
        for (Weapon* w : weapons) {
            if (w->getType() == "Torpedo") {
                count++;
            }
        }
        return count;
    }

    int findGunnerCount() const {
        int count = 0;
        for (Weapon* w : weapons) {
            if (w->getType() == "Light Cannon") {
                count++;
            }
        }
        return count;
    }

    void attack(vector<Ship*>& enemies) override {
        for (Weapon* w : weapons){
            Ship* target = getRandomEnemy(enemies);
            if (!target) return;

            if (didHit(this->getHitChance())) {
                int damage = w->getPower();
                target->takeDamage(damage);

                cout << shipType << " " << name << " hits " << target->getShipType() << " " << target->getName()
                     << " with " << w->getType() << " for " << damage << " damage\n";
            } else {
                cout << shipType << " " << name << " misses " << target->getShipType() << " " << target->getName() << " With " << w->getType() << endl;
            }
        }
    }

    void printDetails() override{
        cout << "[" << id << "] " << "  " << name << "  " << "(" << shipType << ")\n";
        cout << "   HP: " << hitPoints << "/" << maxHitPoints << "\n";
        cout << "   Pilots (" << pilot.size() << "/" << maxPilot << "):";
        bool first = true;
        for (CrewMember* p : pilot){
            if (!first) {
            cout << ", ";
            }
            cout << " " << p->getName();
            first = false;
        }
        cout << "\n";
        cout << "   Gunners (" << findGunnerCount() << "/" << maxCannon << "): ";
        first = true;
        for (Weapon* w : weapons){
            if (w->getType() == "Torpedo"){
                continue;
            }
            if (!first) {
            cout << ", ";
            }
            cout << w->getCrew()->getName();
            first = false;
        }
        cout << "\n";
        cout << "   Torp Handlers (" << findTorpedoCount() << "/" << maxTorpedo << "): ";
        first = true;
        for (Weapon* w : weapons){
            if (w->getType() == "Light Cannon"){
                continue;
            }
            if (!first) {
            cout << ", ";
            }
            cout << w->getCrew()->getName();
            first = false;
        }
        cout << "\n";
    }

};


void removeDestroyedShips(vector<Ship*>& ships); //foward declaration for battle engine

class BattleEngine {
private:
    vector<Ship*>& zShips;
    vector<Ship*>& rShips;
    int round;

    void executeRound() {
        // Zapezoids attack
        for (Ship* s : zShips) {
            s->attack(rShips);
        }

        // Rogoatuskans attack
        for (Ship* s : rShips) {
            s->attack(zShips);
        }
    }

    void cleanup() {
        removeDestroyedShips(zShips);
        removeDestroyedShips(rShips);
    }

    void printStatus() const {
        cout << "\n--- Ship Status ---\n";

        cout << "Zapezoids:\n";
        for (Ship* s : zShips) {
            cout << "   " << "[" << s->getID() << "] " << s->getShipType() << " " << s->getName()
                 << " (" << s->getHitPoints() << "/" << s->getMaxHitPoints() << ")\n";
        }
        if (zShips.empty()) {
            cout << "All Zapezoid ships have been destroyed!\n";
        }

        cout << "Rogoatuskans:\n";
        for (Ship* s : rShips) {
            cout << "   " << "[" << s->getID() << "] " << s->getShipType() << " " << s->getName()
                 << " (" << s->getHitPoints() << "/" << s->getMaxHitPoints() << ")\n";
        }

        if (rShips.empty()) {
            cout << "All Rogoatuskan ships have been destroyed!\n";
        }

    }

public:
    BattleEngine(vector<Ship*>& z, vector<Ship*>& r)
        : zShips(z), rShips(r), round(1) {}

    void run() {
        while (!zShips.empty() && !rShips.empty()) {
            cout << "\n--- Round " << round << " ---\n";
            executeRound();
            cleanup();
            printStatus();
            round++;
        }

        cout << "\n=== Battle Over ===\n";
        if (zShips.empty() && rShips.empty())
            cout << "Both sides destroyed!\n";
        else if (zShips.empty())
            cout << "Rogoatuskans win!\n";
        else
            cout << "Zapezoids win!\n";
    }
};

void removeDestroyedShips(vector<Ship*>& ships) {
    for (auto it = ships.begin(); it != ships.end(); ) {
        if ((*it)->isDestroyed()) {
            it = ships.erase(it);
        } else {
            ++it;
        }
    }
}

//
// FUNCTION DEFINITION FOR SORTING/CREW ALLOCATION STARTS HERE
//

vector<Ship*> loadShips(const string& filename, bool isZapezoid) {
    vector<Ship*> ships;
    ifstream file(filename);

    if (!file) {
        cerr << "Failed to open file: " << filename << endl;
        return ships;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, type, name;

        getline(ss, id, ',');
        getline(ss, type, ',');
        getline(ss, name, ',');

        trimCR(id);
        trimCR(type);
        trimCR(name);

        if (isZapezoid) {
            if (type == "Guerriero")
                ships.push_back(new Guerriero(id, name));
            else if (type == "Medio")
                ships.push_back(new Medio(id, name));
            else if (type == "Corazzata")
                ships.push_back(new Corazzata(id, name));
        } else {
            if (type == "Jager")
                ships.push_back(new Jager(id, name));
            else if (type == "Kreuzer")
                ships.push_back(new Kreuzer(id, name));
            else if (type == "Fregatte")
                ships.push_back(new Fregatte(id, name));
        }
    }

    return ships;
}

vector<CrewMember*> loadCrew(const string& filename) {
    vector<CrewMember*> crew;
    ifstream file(filename);

    if (!file) {
        cerr << "Failed to open file: " << filename << endl;
        return crew;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, role;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, role, ',');

        trimCR(idStr);
        trimCR(name);
        trimCR(role);

        string id = idStr;
        crew.push_back(new CrewMember(id, name, role));
    }

    return crew;
}

void assignCrewToShips(vector<Ship*>& ships, vector<CrewMember*>& crew) {
    int shipIndex = 0;

    for (CrewMember* c : crew) {
        ships[shipIndex]->addCrew(c);
        shipIndex = (shipIndex + 1) % ships.size();
    }
}

void FilterPilotandGunner(vector<CrewMember*>& Crew, queue<CrewMember*>& Pilot, queue<CrewMember*>& Gunner){
    for (CrewMember* c : Crew) {
        if (c ->getRole() == "Pilot"){
            Pilot.push(c);
        }
        else{
            Gunner.push(c);
        }
    }
}

void assignPilotsToShips(vector<Ship*>& ships, queue<CrewMember*>& pilot) {
    //spread pilot equally, then add more to leftover slots
    vector<Ship*> shipIndex; //ship with extra pilot slot
    for (Ship* s : ships){
        if (pilot.empty()){
            break;
        }
        s->addPilot(pilot.front());
        s->addCrew(pilot.front());
        pilot.pop();
        if((s->getMaxPilot()) > s->getPilotCount()){
            shipIndex.push_back(s);
        };
    }

    if (!pilot.empty() && !shipIndex.empty()){
        assignPilotsToShips(shipIndex, pilot); //recursive until pilot or slot ran out
    }
}

void assignWeaponsToShips(vector<Ship*>& ships, queue<CrewMember*>& gunner, int iteration = 1) {
    //spread gunner and torpedo handler evenly through recursion, if the ship possess both slots then both gunner and torpedo will be added together
    vector<Ship*> leftOverShips; //ships that have more than 1 gun or torpedo will be added here for recursion
    for (Ship* s : ships) {
        if (gunner.empty()){
            break;
        }

        // Zapezoid ships
        if (dynamic_cast<Guerriero*>(s)) {
            dynamic_cast<Guerriero*>(s)->setPilotasGunner(); //pilot = gunner
        }
        else if (dynamic_cast<Medio*>(s)) { //search the gunner vector for light cannon gunner, rotate the crew if torpedo is met
            bool foundGunner = false;
            int count = gunner.size();
            for (int i = 0; i < count; i++){
                if(gunner.front()->getRole() == "TorpedoHandler"){
                    gunner.push(gunner.front());
                    gunner.pop();
                }
                else{
                    s->addCrew(gunner.front());
                    s->addWeapon(new Weapon("Light Cannon", 134, gunner.front()));
                    gunner.pop();
                    foundGunner = true;
                }
                if (foundGunner){
                    if(s-> getMaxCannon() - iteration > 0){
                        leftOverShips.push_back(s);
                    }
                    break;
                }
            }
        }
        else if (dynamic_cast<Corazzata*>(s)) {
            bool foundGunner = false;
            bool foundTorpedo = false;
            int count = gunner.size();
            for (int i = 0; i < count; i++){//add 1 gunner and torpedo, iteration < 5 checks if it already have 5 torpedoers or not
                if(gunner.front()->getRole() == "TorpedoHandler" && iteration < 5 && !foundTorpedo){
                    s->addCrew(gunner.front());
                    s->addWeapon(new Weapon("Torpedo", 293, gunner.front()));
                    gunner.pop();
                    foundTorpedo = true;
                }
                else if (gunner.front()->getRole() == "Gunner" && !foundGunner){
                    s->addCrew(gunner.front());
                    s->addWeapon(new Weapon("Light Cannon", 164, gunner.front()));
                    gunner.pop();
                    foundGunner = true;
                }
                else{
                    gunner.push(gunner.front());
                    gunner.pop();
                }

                if (foundTorpedo && foundGunner){
                    break;
                }
            }

            if(s-> getMaxCannon() - iteration > 0){
                leftOverShips.push_back(s);
            }
        }

        // Rogoatuskan ships
        // same logic applies below
        else if (dynamic_cast<Jager*>(s)) {
            dynamic_cast<Jager*>(s)->setPilotasGunner();
        }
        else if (dynamic_cast<Kreuzer*>(s)) {
            bool foundGunner = false;
            int count = gunner.size();
            for (int i = 0; i < count; i++){
                if(gunner.front()->getRole() == "TorpedoHandler"){
                    gunner.push(gunner.front());
                    gunner.pop();
                }
                else{
                    s->addCrew(gunner.front());
                    s->addWeapon(new Weapon("Light Cannon", 132, gunner.front()));
                    gunner.pop();
                    foundGunner = true;
                }
                if (foundGunner){
                    if(s-> getMaxCannon() - iteration > 0){
                        leftOverShips.push_back(s);
                    }
                    break;
                }
            }
        }
        else if (dynamic_cast<Fregatte*>(s)) {
            bool foundGunner = false;
            bool foundTorpedo = false;
            int count = gunner.size();
            for (int i = 0; i < count; i++){
                if(gunner.front()->getRole() == "TorpedoHandler" && iteration < 6 && !foundTorpedo){
                    s->addCrew(gunner.front());
                    s->addWeapon(new Weapon("Torpedo", 282, gunner.front()));
                    gunner.pop();
                    foundTorpedo = true;
                }
                else if (gunner.front()->getRole() == "Gunner" && !foundGunner){
                    s->addCrew(gunner.front());
                    s->addWeapon(new Weapon("Light Cannon", 159, gunner.front()));
                    gunner.pop();
                    foundGunner = true;
                }
                else{
                    gunner.push(gunner.front());
                    gunner.pop();
                }

                if (foundTorpedo && foundGunner){
                    break;
                }
            }

            if(s-> getMaxCannon() - iteration > 0){
                leftOverShips.push_back(s);
            }
        }
    }
        if (!gunner.empty() && !leftOverShips.empty()){
            iteration++;
            assignWeaponsToShips(leftOverShips, gunner, iteration);
        }
}

int main(int argc, char* argv[]) {

    srand(static_cast<unsigned>(time(nullptr)));

    if (argc != 5) {
        cerr << "Usage: AntaresTT6L zShips.csv zCrew.csv rShips.csv rCrew.csv\n";
        return 1;
    }

    string zShipsFile = argv[1];
    string zCrewFile  = argv[2];
    string rShipsFile = argv[3];
    string rCrewFile  = argv[4];

    // Load ships
    vector<Ship*> zShips = loadShips(zShipsFile, true);
    vector<Ship*> rShips = loadShips(rShipsFile, false);

    // Load crew
    vector<CrewMember*> zCrew = loadCrew(zCrewFile);
    vector<CrewMember*> rCrew = loadCrew(rCrewFile);

    cout << "Loaded " << zShips.size() << " Zapezoid ships\n";
    cout << "Loaded " << rShips.size() << " Rogoatuskan ships\n";
    cout << "Loaded " << zCrew.size() << " Zapezoid crew\n";
    cout << "Loaded " << rCrew.size() << " Rogoatuskan crew\n";

    // Filter Pilot and Gunner
    queue<CrewMember*> zPilot;
    queue<CrewMember*> zGunner;
    queue<CrewMember*> rPilot;
    queue<CrewMember*> rGunner;

    FilterPilotandGunner(zCrew, zPilot, zGunner);
    FilterPilotandGunner(rCrew, rPilot, rGunner);

    cout << "Found " << zPilot.size() << " pilots in Team z\n";
    cout << "Found " << zGunner.size() << " gunner and torpedo handler in Team z\n";
    cout << "Found " << rPilot.size() << " pilots in Team r\n";
    cout << "Found " << rGunner.size() << " gunner and torpedo handler in Team z\n";

    // Assign pilot to ship
    assignPilotsToShips(zShips, zPilot);
    assignPilotsToShips(rShips, rPilot);

    cout << zPilot.size() << " leftover pilots in z\n";
    cout << rPilot.size() << " leftover pilots in r\n";

    cout << "Pilots assigned to ships\n";

    // Assign weapons 
    assignWeaponsToShips(zShips, zGunner);
    assignWeaponsToShips(rShips, rGunner);

    cout << zGunner.size() << " leftover gunner or torpedo handler in Team z\n";
    cout << rGunner.size() << " leftover gunner or torpedo handler in Team r\n";

    cout << "Weapons assigned to ships\n\n";

    // Print ship details
    cout << "========================================\n";
    cout << "       FLEET CONFIGURATION REPORT       \n";
    cout << "========================================\n\n";

    cout<< "--- ZAPEZOID FLEET ---\n";
    for (Ship* s : zShips) {
        s->printDetails();
        cout << "--------------------------------------------------\n";
    }
    
    if (!zPilot.empty() || !zGunner.empty()){
        cout << "Leftover Zapezoid Crew Members:\n";
        while (!zPilot.empty()){
            CrewMember* c = zPilot.front();
            cout << "- " << c->getName() << " (" << c->getRole() << ")\n";
            zPilot.pop();
        }
        while (!zGunner.empty()){
            CrewMember* c = zGunner.front();
            cout << "- " << c->getName() << " (" << c->getRole() << ")\n";
            zGunner.pop();
        }
        cout << "\n";

    }

    cout<< "\n--- ROGOATUSKAN FLEET ---\n";
    for (Ship* s : rShips) {
        s->printDetails();
        cout << "--------------------------------------------------\n";
    }

    if (!rPilot.empty() || !rGunner.empty()){
        cout << "Leftover Rogoatuskan Crew Members:\n";
        while (!rPilot.empty()){
            CrewMember* c = rPilot.front();
            cout << "- " << c->getName() << " (" << c->getRole() << ")\n";
            rPilot.pop();
        }
        while (!rGunner.empty()){
            CrewMember* c = rGunner.front();
            cout << "- " << c->getName() << " (" << c->getRole() << ")\n";
            rGunner.pop();
        }

    }

    // Battle simulation
    BattleEngine engine(zShips, rShips);
    engine.run();
    return 0;
}