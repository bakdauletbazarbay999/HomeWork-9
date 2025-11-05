// Composite
#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

class FileSystemComponent {
public:
    virtual void Display(string indent = "") const = 0;
    virtual int GetSize() const = 0;
    virtual string GetName() const = 0;
    virtual ~FileSystemComponent() {}
};
class File : public FileSystemComponent {
    string name;
    int size;
public:
    File(const string& n, int s) : name(n), size(s) {}
    void Display(string indent = "") const override {
        cout << indent << "- File: " << name << " (" << size << " KB)\n";
    }
    int GetSize() const override { return size; }
    string GetName() const override { return name; }
};
class Directory : public FileSystemComponent {
    string name;
    vector<shared_ptr<FileSystemComponent>> components;
public:
    Directory(const string& n) : name(n) {}

    void Add(shared_ptr<FileSystemComponent> comp) {
        for (auto& c : components)
            if (c->GetName() == comp->GetName()) {
                cout << "Component '" << comp->GetName() << "' already exists in " << name << endl;
                return;
            }
        components.push_back(comp);
    }

    void Remove(const string& compName) {
        for (auto it = components.begin(); it != components.end(); ++it) {
            if ((*it)->GetName() == compName) {
                components.erase(it);
                cout << "Removed '" << compName << "' from " << name << endl;
                return;
            }
        }
        cout << "Component '" << compName << "' not found in " << name << endl;
    }
    void Display(string indent = "") const override {
        cout << indent << "+ Directory: " << name << "\n";
        for (auto& c : components)
            c->Display(indent + "   ");
    }
    int GetSize() const override {
        int total = 0;
        for (auto& c : components)
            total += c->GetSize();
        return total;
    }
    string GetName() const override { return name; }
};
int main() {
    auto root = make_shared<Directory>("Root");
    auto docs = make_shared<Directory>("Documents");
    auto pics = make_shared<Directory>("Pictures");

    auto file1 = make_shared<File>("Resume.docx", 120);
    auto file2 = make_shared<File>("Budget.xlsx", 200);
    auto file3 = make_shared<File>("photo1.jpg", 350);
    auto file4 = make_shared<File>("photo2.jpg", 500);

    docs->Add(file1);
    docs->Add(file2);
    pics->Add(file3);
    pics->Add(file4);

    root->Add(docs);
    root->Add(pics);

    root->Display();
    cout << "\nTotal size of Root: " << root->GetSize() << " KB\n";

    docs->Remove("Resume.docx");
    root->Display();
    cout << "\nUpdated total size: " << root->GetSize() << " KB\n";

    return 0;
}
