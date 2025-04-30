#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>

uint8_t find_val(int w, int h, int x, int y, std::vector<std::vector<uint8_t>>& v)
{
    if(x>=0 && x<h && y>=0 && y<w)
        return v[x][y];
    else{
        if(x<0)
        {
            if (y>=0 && y<w)
                return v[0][y];
            else {
                if (y<0)
                    return v[0][0];
                else return v[0][w-1];
            }
        }
        else if(x>=h)
        {
            if (y>=0 && y<w)
                return v[h-1][y];
            else {
                if (y<0)
                    return v[h-1][0];
                else return v[h-1][w-1];
            }
        }
        else {
            if (y<0)
                return v[x][0];
            else return v[x][w-1];
        }
    }
}

void bubbleSort(std::vector<uint8_t>& v) {
    int n = v.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

void merge(std::vector<uint8_t>& v, int left, int mid, int right) {
    std::vector<uint8_t> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (v[i] <= v[j]) temp[k++] = v[i++];
        else temp[k++] = v[j++];
    }
    while (i <= mid) temp[k++] = v[i++];
    while (j <= right) temp[k++] = v[j++];
    for (int i = left; i <= right; ++i) v[i] = temp[i - left];
}

void mergeSort(std::vector<uint8_t>& v, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(v, left, mid);
        mergeSort(v, mid + 1, right);
        merge(v, left, mid, right);
    }
}

int main()
{
    std::string tip, name1, name2;
    int dim, width, height;
    std::vector<uint8_t> bord;
    std::vector<std::vector<uint8_t>> v;
    std::cin>>tip>>dim>>name1>>name2;
    std::ifstream fin;
    std::ofstream fout;
    fin.open(name1, std::ios::out);
    fout.open(name2, std::ios::out);
    std::string name;
    fin>>name;
    fin.ignore();
    std::string linie;
    while(std::getline(fin, linie))
    {
        if(linie[0] == '#')
        {
            continue;
        }
        else{
            break;
        }
    }
   std::string t;
    std::stringstream ss(linie);
    getline(ss, t, ' ');
    width = stoi(t);
    getline(ss, t, ' ');
    height = stoi(t);
    while(std::getline(fin, linie))
    {
        if(linie[0] == '#')
        {
            continue;
        }
        else{
            break;
        }
    }
    int maxalb;
    maxalb = stoi(linie);
    for(int i=0; i<height; i++)
    {
        std::vector<uint8_t> linii;
        for(int j=0; j<width; j++)
        {
            int a;
            fin>>a;
            uint8_t b = a;
            linii.push_back(b);
        }
        v.push_back(linii);
    }
    fout<<name<<"\n";
    fout<<width<<' '<<height<<"\n";
    fout<<maxalb<<"\n";
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++) {
            bord.clear();
            for(int x=i-(dim-1)/2; x<=i+(dim-1)/2; x++)
            {
                for(int y=j-(dim-1)/2; y<=j+(dim-1)/2; y++)
                {
                    bord.push_back(find_val(width, height, x, y, v));
                }
            }

            if (dim>1) {
                if(tip == "bubble")
                {
                    bubbleSort(bord);
                }
                if(tip == "merge") {
                    mergeSort(bord, 0, bord.size()-1);
                }
                int vout = bord[bord.size()/2];
                fout<<vout<<' ';
            }
            else {
                int vout = v[i][j];
                fout<<vout<<' ';
            }
        }
        fout<<'\n';
    }
    fin.close();
    fout.close();
    return 0;
}