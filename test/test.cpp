int Solucao::calcJanela(Agenda *professor)
{

    int dias[6];
    int janelaHorarios = 0;

    for (int dia = 0; dia < 6; dia++)
    {

        int slotInicio = 0;
        int slotFim = 0;

        // If the resource has no activity in the given day, go to the next day
        if (dias[dia] == 0)
        {
            continue;
        }

        // Manhã
        for (int slot = 0; slot < 6; slot++)
        {
            if (professor->agenda[dia][slot] > 0)
            {
                slotInicio = slot;
                break;
            }
        }
        for (int slot = 5; slot >= 0; slot--)
        {
            if (professor->agenda[dia][slot] > 0)
            {
                slotFim = slot;
                break;
            }
        }

        for (int slot = slotInicio + 1; slot < slotFim; slot++)
        {
            if (professor->agenda[dia][slot] <= 0)
            {
                janelaHorarios++;
            }
        }

        slotInicio = 0;
        slotFim = 0;

        // Tarde
        for (int slot = 6; slot < 12; slot++)
        {
            if (professor->agenda[dia][slot] > 0)
            {
                slotInicio = slot;
                break;
            }
        }
        for (int slot = 11; slot >= 6; slot--)
        {
            if (professor->agenda[dia][slot] > 0)
            {
                slotFim = slot;
                break;
            }
        }

        for (int slot = slotInicio + 1; slot < slotFim; slot++)
        {
            if (professor->agenda[dia][slot] <= 0)
            {
                janelaHorarios++;
            }
        }

        slotInicio = 0;
        slotFim = 0;

        // Noite
        for (int slot = 12; slot < 16; slot++)
        {
            if (professor->agenda[dia][slot] > 0)
            {
                slotInicio = slot;
                break;
            }
        }
        for (int slot = 15; slot >= 12; slot--)
        {
            if (professor->agenda[dia][slot] > 0)
            {
                slotFim = slot;
                break;
            }
        }

        for (int slot = slotInicio + 1; slot < slotFim; slot++)
        {
            if (professor->agenda[dia][slot] <= 0)
            {
                janelaHorarios++;
            }
        }
    }

    cout << "\033[0m";

    if (janelaHorarios > 0)
    {
        professor->printAgenda();
    }

    return janelaHorarios;
}