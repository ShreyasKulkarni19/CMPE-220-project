// Shift code to remove tab characters and separate instructions
void shift()
{
    int codeSize = codeinit.size();
    for (int i = 0; i < codeSize; i++)
    {
        // Replace tab characters with spaces
        for (int j = 0; j < codeinit[i].size(); j++)
        {
            if (codeinit[i][j] == '\t')
            {
                codeinit[i][j] = ' ';
            }
        }

        // Extract instruction from the line
        string instruction;
        int j = 0;
        int startIndex = -1;
        while (j < codeinit[i].size() && codeinit[i][j] == ' ')
        {
            j++;
        }
        startIndex = j;
        while (j < codeinit[i].size() && codeinit[i][j] != ' ')
        {
            instruction += codeinit[i][j];
            j++;
            if (j < codeinit[i].size() && codeinit[i][j] == ':')
            {
                instruction += codeinit[i][j];
                j++;
                break;
            }
        }

        // Check if instruction is a pseudo command
        if (instruction == "la")
        {
            processla(i);
            continue;
        }
        else if (instruction == "lw" || instruction == "lb" || instruction == "lhw")
        {
            string label;
            int j = codeinit[i].size() - 1;
            while (codeinit[i][j] == ' ')
            {
                j--;
            }
            while (codeinit[i][j] != ' ')
            {
                label += codeinit[i][j];
                j--;
            }
            reverse(label.begin(), label.end());
            int flag = 1;
            for (int j = 0; j < datalabel.size(); j++)
            {
                if (label.compare(datalabel[j].name) == 0)
                {
                    flag = 0;
                    processlw(instruction, i, datalabel[j].position);
                    break;
                }
            }
            if (!flag)
            {
                continue;
            }
        }

        // Check if instruction matches predefined formats
        for (int k = 0; k < sizeI; k++)
        {
            string type;
            int k1 = 0;
            while (Format[k][k1] != ' ')
            {
                type += (Format[k][k1]);
                k1++;
            }
            if (instruction.compare(type) == 0)
            {
                string extracted;
                for (int k = startIndex; k < codeinit[i].size(); k++)
                {
                    extracted += codeinit[i][k];
                }
                code.push_back(extracted);
                break;
            }
        }
    }
}

// Extract labels from code
void extractLabels()
{
    int codeSize = codeinit.size();
    int labelIndex = -1;
    for (int i = 0; i < codeSize; i++)
    {
        string instruction;
        int j = 0;
        int startIndex = -1;
        while (j < codeinit[i].size() && codeinit[i][j] == ' ')
        {
            j++;
        }
        startIndex = j;
        while (j < codeinit[i].size() && codeinit[i][j] != ' ')
        {
            instruction += codeinit[i][j];
            j++;
            if (j < codeinit[i].size() && codeinit[i][j] == ':')
            {
                instruction += codeinit[i][j];
                j++;
                break;
            }
        }
        int instructionSize = instruction.size();
        if (instruction[instructionSize - 1] == ':')
        {
            string labelName;
            for (int k = 0; k < instructionSize - 1; k++)
            {
                labelName += instruction[k];
            }
            lab temp;
            temp.s = labelName;
            temp.index = labelIndex + 1;
            Label.push_back(temp);
        }
        if (instruction[instructionSize - 1] == ':' && instructionSize < codeinit[i].size())
        {
            while (j < codeinit[i].size() && codeinit[i][j] == ' ')
            {
                j++;
            }
            instruction.clear();
            while (j < codeinit[i].size() && codeinit[i][j] != ' ')
            {
                instruction += codeinit[i][j];
                j++;
            }
        }
        if (instruction == "la")
        {
            labelIndex += 2;
            continue;
        }
        else if (instruction == "lw" || instruction == "lb" || instruction == "lhw")
        {
            string label;
            int j = codeinit[i].size() - 1;
            while (codeinit[i][j] == ' ')
            {
                j--;
            }
            while (codeinit[i][j] != ' ')
            {
                label += codeinit[i][j];
                j--;
            }
            reverse(label.begin(), label.end());
            int flag = 1;
            for (int j = 0; j < datalabel.size(); j++)
            {
                if (label.compare(datalabel[j].name) == 0)
                {
                    flag = 0;
                    labelIndex += 2;
                    break;
                }
            }
            if (!flag)
            {
                continue;
            }
        }
        for (int k = 0; k < sizeI; k++)
        {
            string type;
            int k1 = 0;
            while (Format[k][k1] != ' ')
            {
                type += (Format[k][k1]);
                k1++;
            }
            if (instruction.compare(type) == 0)
            {
                labelIndex++;
                break;
            }
        }
    }
}
