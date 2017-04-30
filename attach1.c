int edge_split(int ind)
{
    int i;
    Vert mid = calc_ed_midp(EdgeMass[ind]);
    Diamond D;

    if(!(EdgeMass[ind].sw))
    {
        printf("Trying to split delited edge!\n");
        return 1;
    }

    D = edge_diamond(ind);
    if(!D.val || ed_num >= DEF_EDGE_MASS_SIZE - 4)
    {
        return 1;
    }
    i = 0;
    while(i < 4 && D.vert[i].x != -1)
    {
        add_edge(D.vert[i], mid, ed_num + i);
        i++;
    }
    ed_num += i;
    EdgeMass[ed_num].sw = 0;

    EdgeMass[ind].sw = 0;

    return 0;
}

int edge_collapse(int ind)
{
    int i;
    Star S;
    Vert mid = calc_ed_midp(EdgeMass[ind]);

    if(!(EdgeMass[ind].sw))
    {
        printf("Trying to collapse delited edge!\n");
        return 1;
    }

    if(ed_num >= DEF_EDGE_MASS_SIZE - DEF_SV_MASS_SIZE)
    {
        return 1;
    }

    EdgeMass[ind].sw = 0;

    S  = edge_star(ind);
    if(S.length == -1)
    {
        return 1;
    }
    if(S.length == 0)
    {
        EdgeMass[ind].sw = 1;
        return 0;
    }

    for(i = 0; i < S.length; ++i)
    {
        add_edge(mid, S.vert[i], ed_num);
        ed_num++;
    }
    EdgeMass[ed_num].sw = 0;

    return 0;
}
