#include "NumberWithUnits.hpp"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace ariel;
using namespace std;
namespace ariel 
{

    unordered_map<string,unit> NumberWithUnits::map = std::unordered_map<std::string,ariel::unit>();
    bool NumberWithUnits::checkKey(string key)const {
        return map.find(key)!=map.end();
    }
    void NumberWithUnits::read_units(ifstream & stream){
        if(stream.fail())
            exit(1);
        while(!stream.eof()){
            string type, gar;
            ariel::unit u,t;
            stream >> gar >> type >> gar >> u.value >>u.s;
            map[type] = u;

            if(map.find(u.s) == map.end()){
                t.value=1;
                t.s = u.s;
                map[u.s] = t;
            }
        }
    }
    bool NumberWithUnits::way(string t1, string t2)const {
        if (t1==t2)
            return true;
        if(map.find(t1) == map.end() || map.find(t2)== map.end())
            return false;
        ariel::unit temp;
        temp = map[t1];
        while( temp.s != map[temp.s].s && temp.s!=t2){
            temp = map[temp.s];
        }
        return temp.s == t2;
    }
    string find_common(unordered_map<string,ariel::unit>map,string t1, string t2){
        ariel::unit temp,temp2;
        temp = map[t1];
        while( temp.s != map[temp.s].s){
            temp = map[temp.s];
        }
        temp2 = map[t2];
        while( temp2.s != map[temp2.s].s){
            temp2 = map[temp2.s];
        }
        if (temp2.s == temp.s)
            return temp.s;
        else
            return "";
    }
    double multway(unordered_map<string,ariel::unit>map,string t1, string t2){
        if (t1 == t2)
            return 1;
        ariel::unit t = map[t1];
        double s = 1;
        while(t.s != t2){
            s *= t.value;
            t = map[t.s];
        }
        return s*t.value;
    }
    NumberWithUnits NumberWithUnits::convert (string t1, string t2, double v) const {
        string common;
        if (t1 == t2)
            return NumberWithUnits(v, t1);
        if (this -> way(t1, t2)){
            double ratio = 1.0 / multway(map, t1, t2);
            NumberWithUnits ret(ratio * v, t1);    
            return ret;
        }
        else if (this -> way(t2, t1)){
            double ratio = multway(map, t2, t1);
            NumberWithUnits ret(ratio * v, t1);    
            return ret;
        }
        else if ((common = find_common(map, t1, t2)) != "" ){
            NumberWithUnits n = convert(common, t2, v);
            return convert(t1, common, n.value);
        }
        else
            throw logic_error("Units dont match: "+t2+" cant be converted to "+t1);
    }
    NumberWithUnits NumberWithUnits::operator+ (const NumberWithUnits &other) const{
        if (other.getunit() == this->getunit()){
            return NumberWithUnits(this->getvalue() + other.getvalue(), this->getunit());
        }
        NumberWithUnits n = this->convert(this -> getunit(), other.getunit(), other.getvalue());
        return *(this) + n;
    } 
    NumberWithUnits NumberWithUnits::operator += (const NumberWithUnits& other){
        NumberWithUnits n = convert(this->unit, other.getunit(), other.value);
        this->value += n.value;
        return (*this);
    }
    NumberWithUnits NumberWithUnits::operator+ ()const{
        NumberWithUnits n = *this;
        return n;
    } 

    NumberWithUnits NumberWithUnits::operator- (const NumberWithUnits &other)const{
        if (other.getunit() == this -> getunit()){
            return NumberWithUnits(this->getvalue()-other.getvalue(),this->getunit());
        }
        NumberWithUnits n = this->convert(this->getunit(),other.getunit(),other.getvalue());
        return *(this) - n;
    } 
    NumberWithUnits NumberWithUnits::operator-=(const NumberWithUnits& other){
        NumberWithUnits n = this->convert(this->getunit(), other.getunit(),other.getvalue());
        this->value -= n.value;
        return (*this);
    }
    NumberWithUnits NumberWithUnits::operator-()const{
        NumberWithUnits n = *this;
        n.value = -n.value;
        return n;
    } 

    NumberWithUnits & NumberWithUnits::operator++(){
        this->value += 1;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int dummy){
        NumberWithUnits u = *this;
        this->value+=1;
        return u;
    }

    NumberWithUnits & NumberWithUnits::operator--(){
        this->value -= 1;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int dummy){
        NumberWithUnits u = *this;
        this->value-=1;
        return u;
    }


    bool  NumberWithUnits::operator<(const NumberWithUnits & other)const{
        NumberWithUnits n = convert(this->unit,other.unit,other.value);
        return this->value < n.value;
    }
    bool  NumberWithUnits::operator<=(const NumberWithUnits & other)const{
        NumberWithUnits n = convert(this->unit,other.unit,other.value);
        return this->value <= n.value;
    }
    bool  NumberWithUnits::operator>(const NumberWithUnits & other)const{
        NumberWithUnits n = convert(this->unit,other.unit,other.value);
        return this->value > n.value;

    }
    bool  NumberWithUnits::operator>=(const NumberWithUnits & other)const{
        NumberWithUnits n = convert(this->unit,other.unit,other.value);
        return this->value >= n.value;
    }
    bool  NumberWithUnits::operator==( const NumberWithUnits& other)const{
        NumberWithUnits n = convert(this->unit,other.unit,other.value);
        double epsilon = 0.0001;
        return abs(this->value - n.value) <= epsilon;
    }
    bool  NumberWithUnits::operator!=(const NumberWithUnits & other)const{
        NumberWithUnits n = convert(this->unit,other.unit,other.value);
        return this->value != n.value;
    }

    ostream & operator << (ostream & os, const NumberWithUnits & other){
        os << other.value <<"[" <<other.unit << "]";
        return os;
    }

    istream & operator >> (istream & is, NumberWithUnits & other){
        string g,s1;
        while(!is.eof()){
            is >> s1;
            g+=s1;
            if(s1.at(s1.length()-1) == ']')
                break;
        }
        replace(g.begin(), g.end(),'[', ' ');
        replace(g.begin(), g.end(),']', ' ');
        istringstream s = istringstream{g};
        if (!s.eof())
            s >> other.value >> other.unit;
        if(NumberWithUnits::map.find(other.unit) == NumberWithUnits::map.end())
            throw logic_error("unit ["+other.unit+"] doesn't exist.");
        return is;
    }
    NumberWithUnits operator *(double bap,const NumberWithUnits & n){
        NumberWithUnits a = n;
        a.setvalue(a.getvalue()*bap);
        return a;
    }

    NumberWithUnits NumberWithUnits::operator* (double v){
        NumberWithUnits u = *this;
        return v * u;
    }

}