// Antares TT6L
// Member 1: Rashid Hassan Abdalla – 251UC250GF
// Member 2: Mohamed Yassir Mohamed – 251UC25026
// Member 3: Ahmed Ibrahim Mohamed – 251UC2519U
// Member 4: Jeremy Puah – Student ID

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool didHit(int hitChance) {
    int roll = rand() % 100;  // 0–99
    return roll < hitChance;
}

class Ship;

Ship* getRandomEnemy(vector<Ship*>& enemies) {
    if (enemies.empty()) return nullptr;
    int index = rand() % enemies.size();
    return enemies[index];
}

class CrewMember {
private:
    int id;
    string name;
    string role; // pilot, gunner, torpedo_handler

public:
    CrewMember(int id, const string& name, const string& role)
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

public:
    Weapon(const string& type, int power)
        : type(type), power(power) {}

    int getPower() const {
        return power;
    }

    string getType() const {
        return type;
    }
};

Weapon* getLightCannon(const vector<Weapon*>& weapons) {
    for (Weapon* w : weapons) {
        if (w->getType() == "light_cannon")
            return w;
    }
    return nullptr;
}

Weapon* getTorpedo(const vector<Weapon*>& weapons) {
    for (Weapon* w : weapons) {
        if (w->getType() == "torpedo")
            return w;
    }
    return nullptr;
}


class Ship {
protected:
    string name;
    int hitPoints;
    int hitChance;
    vector<CrewMember*> crew;
    vector<Weapon*> weapons;

public:
    Ship(const string& name, int hp, int hitChance)
    : name(name), hitPoints(hp), hitChance(hitChance) {}

    virtual ~Ship() {}

    virtual void attack(vector<Ship*>& enemies) = 0; // abstract

    void takeDamage(int dmg) {
        hitPoints -= dmg;
    }

    bool isDestroyed() const {
        return hitPoints <= 0;
    }

    string getName() const {
        return name;
    }

    int getHitChance() const {
        return hitChance;
    }

    int getHitPoints() const {
        return hitPoints;
    }

    void addCrew(CrewMember* c) {
        crew.push_back(c);
    }

    void addWeapon(Weapon* w) {
        weapons.push_back(w);
    }
};

class Guerriero : public Ship {
public:
    Guerriero(const string& name)
        : Ship(name, 123, 26) {}

    void attack(vector<Ship*>& enemies) override {
        Ship* target = getRandomEnemy(enemies);
        if (!target) return;

        Weapon* cannon = getLightCannon(weapons);
        if (!cannon && !weapons.empty()) {
            cannon = weapons[0];
        }
        if (!cannon) return;

        if (didHit(target->getHitChance())) {
            int damage = cannon->getPower();
            target->takeDamage(damage);

            cout << name << " hits " << target->getName()
                 << " with light cannon for "
                 << damage << " damage\n";
        } else {
            cout << name << " misses " << target->getName() << endl;
        }
    }
};

class Medio : public Ship {
public:
    Medio(const string& name)
        : Ship(name, 214, 31) {}

    void attack(vector<Ship*>& enemies) override {
        Ship* target = getRandomEnemy(enemies);
        if (!target) return;

        Weapon* cannon = getLightCannon(weapons);
        if (!cannon && !weapons.empty()) {
            cannon = weapons[0];
        }
        if (!cannon) return;

        if (didHit(target->getHitChance())) {
            int damage = cannon->getPower();
            target->takeDamage(damage);

            cout << name << " hits " << target->getName()
                 << " with light cannon for "
                 << damage << " damage\n";
        } else {
            cout << name << " misses " << target->getName() << endl;
        }
    }
};

class Corazzata : public Ship {
public:
    Corazzata(const string& name)
        : Ship(name, 1031, 50) {}

    void attack(vector<Ship*>& enemies) override {
        Ship* target = getRandomEnemy(enemies);
        if (!target) return;

        Weapon* cannon = getLightCannon(weapons);
        if (!cannon && !weapons.empty()) {
            cannon = weapons[0];
        }
        if (!cannon) return;

        if (didHit(target->getHitChance())) {
            int damage = cannon->getPower();
            target->takeDamage(damage);

            cout << name << " hits " << target->getName()
                 << " with light cannon for "
                 << damage << " damage\n";
        } else {
            cout << name << " misses " << target->getName() << endl;
        }
    }
};

class Jager : public Ship {
public:
    Jager(const string& name)
        : Ship(name, 112, 24) {}

    void attack(vector<Ship*>& enemies) override {
        Ship* target = getRandomEnemy(enemies);
        if (!target) return;

        Weapon* cannon = getLightCannon(weapons);
        if (!cannon && !weapons.empty()) {
            cannon = weapons[0];
        }
        if (!cannon) return;

        if (didHit(target->getHitChance())) {
            int damage = cannon->getPower();
            target->takeDamage(damage);

            cout << name << " hits " << target->getName()
                 << " with light cannon for "
                 << damage << " damage\n";
        } else {
            cout << name << " misses " << target->getName() << endl;
        }
    }
};

class Kreuzer : public Ship {
public:
    Kreuzer(const string& name)
        : Ship(name, 212, 29) {}

    void attack(vector<Ship*>& enemies) override {
        Ship* target = getRandomEnemy(enemies);
        if (!target) return;

        Weapon* cannon = getLightCannon(weapons);
        if (!cannon && !weapons.empty()) {
            cannon = weapons[0];
        }
        if (!cannon) return;

        if (didHit(target->getHitChance())) {
            int damage = cannon->getPower();
            target->takeDamage(damage);

            cout << name << " hits " << target->getName()
                 << " with light cannon for "
                 << damage << " damage\n";
        } else {
            cout << name << " misses " << target->getName() << endl;
        }
    }
};

class Fregatte : public Ship {
public:
    Fregatte(const string& name)
        : Ship(name, 1143, 60) {}

    void attack(vector<Ship*>& enemies) override {
        Ship* target = getRandomEnemy(enemies);
        if (!target) return;

        Weapon* cannon = getLightCannon(weapons);
        if (!cannon && !weapons.empty()) {
            cannon = weapons[0];
        }
        if (!cannon) return;

        if (didHit(target->getHitChance())) {
            int damage = cannon->getPower();
            target->takeDamage(damage);

            cout << name << " hits " << target->getName()
                 << " with light cannon for "
                 << damage << " damage\n";
        } else {
            cout << name << " misses " << target->getName() << endl;
        }
    }
};

class BattleEngine {
private:
    vector<Ship*> zapezoidShips;
    vector<Ship*> rogoatuskanShips;

public:
    BattleEngine() {}

    void addZapezoidShip(Ship* ship) {
        zapezoidShips.push_back(ship);
    }

    void addRogoatuskanShip(Ship* ship) {
        rogoatuskanShips.push_back(ship);
    }

    void runBattle() {
        // battle logic will be added later
    }
};

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

        if (isZapezoid) {
            if (type == "Guerriero")
                ships.push_back(new Guerriero(name));
            else if (type == "Medio")
                ships.push_back(new Medio(name));
            else if (type == "Corazzata")
                ships.push_back(new Corazzata(name));
        } else {
            if (type == "Jager")
                ships.push_back(new Jager(name));
            else if (type == "Kreuzer")
                ships.push_back(new Kreuzer(name));
            else if (type == "Fregatte")
                ships.push_back(new Fregatte(name));
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

        int id = stoi(idStr);
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

void assignWeaponsToShips(vector<Ship*>& ships) {
    for (Ship* s : ships) {

        // Zapezoid ships
        if (dynamic_cast<Guerriero*>(s)) {
            s->addWeapon(new Weapon("light_cannon", 96));
        }
        else if (dynamic_cast<Medio*>(s)) {
            s->addWeapon(new Weapon("light_cannon", 134));
            s->addWeapon(new Weapon("light_cannon", 134));
        }
        else if (dynamic_cast<Corazzata*>(s)) {
            for (int i = 0; i < 10; i++)
                s->addWeapon(new Weapon("light_cannon", 164));
            for (int i = 0; i < 4; i++)
                s->addWeapon(new Weapon("torpedo", 293));
        }

        // Rogoatuskan ships
        else if (dynamic_cast<Jager*>(s)) {
            s->addWeapon(new Weapon("light_cannon", 96));
        }
        else if (dynamic_cast<Kreuzer*>(s)) {
            s->addWeapon(new Weapon("light_cannon", 134));
            s->addWeapon(new Weapon("light_cannon", 134));
        }
        else if (dynamic_cast<Fregatte*>(s)) {
            for (int i = 0; i < 8; i++)
                s->addWeapon(new Weapon("light_cannon", 164));
            for (int i = 0; i < 4; i++)
                s->addWeapon(new Weapon("torpedo", 293));
        }
    }
}

void removeDestroyedShips(vector<Ship*>& ships) {
    for (auto it = ships.begin(); it != ships.end(); ) {
        if ((*it)->isDestroyed()) {
            it = ships.erase(it);
        } else {
            ++it;
        }
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

    // Assign crew
    assignCrewToShips(zShips, zCrew);
    assignCrewToShips(rShips, rCrew);
    cout << "Crew assigned to ships\n";

    // Assign weapons (temporary simple setup)
    assignWeaponsToShips(zShips);
    assignWeaponsToShips(rShips);
    cout << "Weapons assigned to ships\n";

    // ======================
    // Battle simulation
    // ======================
    int round = 1;

    while (!zShips.empty() && !rShips.empty()) {
        cout << "\n--- Round " << round << " ---\n";

        // Zapezoids attack
        for (Ship* s : zShips) {
            s->attack(rShips);
        }

        // Rogoatuskans attack
        for (Ship* s : rShips) {
            s->attack(zShips);
        }

        // Remove destroyed ships
        removeDestroyedShips(zShips);
        removeDestroyedShips(rShips);

        cout << "Zapezoid ships left: " << zShips.size() << endl;
        cout << "Rogoatuskan ships left: " << rShips.size() << endl;

        round++;
    }

    // ======================
    // Battle result
    // ======================
    cout << "\n=== Battle Over ===\n";

    if (zShips.empty() && rShips.empty()) {
        cout << "Both sides destroyed!\n";
    } else if (zShips.empty()) {
        cout << "Rogoatuskans win!\n";
    } else {
        cout << "Zapezoids win!\n";
    }

    return 0;
}
