    void visualizeTree(const string& dotCode) {
        ofstream dotFile("btree.dot");
        dotFile << dotCode;
        dotFile.close();
        string command = "dot -Tpng btree.dot -o btree.png";
        system(command.c_str());
        system("start btree.png");
    }


    template<class T>
    string generateDotCode(BTreeNode<T>* btreeRoot) {
        std::string dotCode = "digraph BTree {\n";
            dotCode += "\tnode [shape=record, height=.1];\n\n";

            std::queue<BTreeNode<T>*> levelOrderQueue;
            vector<int> idQ;
            levelOrderQueue.push(btreeRoot);
            int count = 0;
            idQ.push_back(count);
            while (!levelOrderQueue.empty()) {
                BTreeNode<T>* current = levelOrderQueue.front();
                levelOrderQueue.pop();
                int j = idQ[0];
                idQ.erase(idQ.begin());
                dotCode += "\tnode" + std::to_string(j) + " [label=\"";
                for (int i = 0; i < current->keys.getSize(); i++) {
                    dotCode += "|" + std::to_string(current->keys[i]);
                }
                dotCode += "|\"];\n";

                for (size_t i = 0; i < current->children.getSize(); ++i) {
                    count++;
                    dotCode += "\tnode" + std::to_string(j) + " -> node" + std::to_string(count) + ";\n";
                    if (current->children[i]->p == current) {
                        dotCode += "\tnode" + std::to_string(count) + " -> node" + std::to_string(j) + ";\n";
                    }
                    idQ.push_back(count);
                    levelOrderQueue.push(current->children[i]);
                }
            }

            dotCode += "}\n";
            return dotCode;
    }

