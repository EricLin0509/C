// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

void bubble(int *p, int len) {
for (int i = 0; i < len; i++)
{
    for (int j = 0; j < len - 1 - i; j++)
    {
        if (*(p+j) < *(p+j+1))
        {
            int temp = *(p+j);
            *(p+j) = *(p+j+1);
            *(p+j+1) = temp;
        }
        
    }
    
}

}
