using System;
using System.Collections.Generic;
using System.Globalization;

namespace GenAlgConsoleApplication
{
  internal class Program
  {
    private const int PERSON_COUNT = 4;
    private const int GEN_COUNT = 8;
    private static List<List<int>> _population;
    private static List<List<int>> _populationAfterCrossingover;
    private static List<List<int>> _tochkiRazriva;
    //�	������������� ��������� +
    //�	������������� +
    //�	������������ +
    //�	�������������� -
    //�	���������������� ����- � ������������ ��������� �������������  +/-
    //�	��������-���������������� ����- � ������������� ���������� ������������� +/-
    //�	������������ ��������� +
    //�	�������� ���������
    //�	����-, ����- � ��� ��������� ���������� �� ������ �������� ��������� �������� � ����� ���������.

    // �������� ���������, ����������� ������ �������� ���������� ������� � �� �������������� ��� ��������� ����� �������� � ����:
    //�) ������� �������;
    //�) �������� �������;
    //�) ������� ������ (����- � ������������);+
    //�) ������� �� ������ �������� ��������� ��������;
    //�) ������� �� ������ ����� ���������;
    //�) ��������;+
    //�) ������������;+
    //�) �������.+


    private static void Main(string[] args)
    {
      //����� ��� ������� ���� ����� � ��� ����� ����� �� 0 �� 8
      //��� ����: ��������!
      GenerateDrobovikPopulation();
      PopulationsShow("��������� ���������");
      CrossingoverOdnotochechniy();
      PopulationsShowAfterAndBeforeCrossingover("����� ������������� �������������", 1);
      CrossingoverDvuhtochechniy();
      PopulationsShowAfterAndBeforeCrossingover("����� ������������� �������������", 2);
      CrossingoverTrehtochechniy();
      PopulationsShowAfterAndBeforeCrossingover("����� ������������� �������������", 3);
      CrossingoverUporyadochenniyOdnotochechniy();
      PopulationsShowAfterAndBeforeCrossingover("����� ������������� �������������� �������������", 1);
      CrossingoverChastichSootvetOdnotochechniy();
      PopulationsShowAfterAndBeforeCrossingover("����� ������������� ��������-���������������� �������������", 1);
      CrossingoverCiklicheskiy();
      PopulationsShowAfterAndBeforeCrossingover("����� ������������� ������������", 0);
      MutationOdnotochechniy();
      PopulationsShowAfterAndBeforeMutation("����� ������� ������������", 1);
      MutationDvuhtochechniy();
      PopulationsShowAfterAndBeforeMutation("����� ������� ������������", 2);
      MutationInversionOdnoTochechnaya();
      PopulationsShowAfterAndBeforeMutation("����� ������� �������� ������������", 1);
      MutationInversionDvuhTochechnaya();
      PopulationsShowAfterAndBeforeMutation("����� ������� �������� ������������", 2);
      CrossingoverMutationTranslakation();
      PopulationsShowAfterAndBeforeCrossingover("����� �������/������������� ������������", 1);
      MutationDeleciyaDvuhTochechnaya();
      PopulationsShowAfterAndBeforeMutation("����� ������� ������� ������������", 2);
    }

    private static void GenerateDrobovikPopulation()
    {
      //���� ��������� �� ����� ������� � ������� ���� ���������� ��������� �����
      _population = new List<List<int>>();
      var rnd = new Random();
      for (int i = 0; i < PERSON_COUNT; i++)
      {
        var gen = new List<int>();
        for (int j = 0; j < GEN_COUNT; j++)
        {
          while (true)
          {
            var currentValue = rnd.Next(0, 8);
            if (!gen.Exists(g = > g == currentValue))
            {
              gen.Add(currentValue);
              break;
            }
          }
        }
        _population.Add(gen);
      }
    }

    private static void CrossingoverOdnotochechniy()
    {
      //����� ������� ������ ������������� ��������� ������������� ������������ ��� ���������� ����� ��, 
      //��� ����������� ����� ��, ������� ������ ������������ ��������.
      //��� ����� ���������� ����� � ���� ����������, ��� ��� ������ ���� �����������.

      _populationAfterCrossingover = new List<List<int>>();
      _tochkiRazriva = new List<List<int>>();
      var rnd = new Random();
      for (var i = 0; i < PERSON_COUNT; i += 2)
      {
        var tochkiRazrivaSub = new List<int>();
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT + 1));
        _tochkiRazriva.Add(tochkiRazrivaSub);
        var newGen = new List<int>();
        var newGen2 = new List<int>();
        for (var j = 0; j < GEN_COUNT; j++)
        {
          if (j >= tochkiRazrivaSub[0])
          {
            newGen.Add(_population[i + 1][j]);
            newGen2.Add(_population[i][j]);
          }
          else
          {
            newGen.Add(_population[i][j]);
            newGen2.Add(_population[i + 1][j]);
          }
        }
        _populationAfterCrossingover.Add(newGen);
        _populationAfterCrossingover.Add(newGen2);
      }
    }

    private static void CrossingoverDvuhtochechniy()
    {
      //� ������ ��������� ������������ ��� ����� ��,
      //� ��������� ������������ ���������, �������������� ����� ����� ������� ��. 
      _populationAfterCrossingover = new List<List<int>>();
      _tochkiRazriva = new List<List<int>>();
      var rnd = new Random();
      for (int i = 0; i < PERSON_COUNT; i += 2)
      {
        var tochkiRazrivaSub = new List<int>();
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT + 1));
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT + 1));
        tochkiRazrivaSub.Sort();
        _tochkiRazriva.Add(tochkiRazrivaSub);

        var newGen = new List<int>();
        var newGen2 = new List<int>();
        for (int j = 0; j < GEN_COUNT; j++)
        {
          if (j >= tochkiRazrivaSub[0] && j < tochkiRazrivaSub[1])
          {
            newGen.Add(_population[i + 1][j]);
            newGen2.Add(_population[i][j]);
          }
          else
          {
            newGen.Add(_population[i][j]);
            newGen2.Add(_population[i + 1][j]);
          }
          _populationAfterCrossingover.Add(newGen);
          _populationAfterCrossingover.Add(newGen2);
        }
      }
      Console.WriteLine();
    }

    private static void CrossingoverTrehtochechniy()
    {
      //� ������ ��������� ������������ ��� ����� ��,
      //� ��������� ������������ ���������, �������������� ����� ����� ������� ��. 
      _populationAfterCrossingover = new List<List<int>>();
      _tochkiRazriva = new List<List<int>>();
      var rnd = new Random();
      for (int i = 0; i < PERSON_COUNT; i += 2)
      {
        var tochkiRazrivaSub = new List<int>();
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT + 1));
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT + 1));
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT + 1));
        tochkiRazrivaSub.Sort();
        _tochkiRazriva.Add(tochkiRazrivaSub);
        var newGen = new List<int>();
        var newGen2 = new List<int>();
        for (int j = 0; j < GEN_COUNT; j++)
        {
          if ((j >= tochkiRazrivaSub[0] && j < tochkiRazrivaSub[1]) || j >= tochkiRazrivaSub[2])
          {
            newGen.Add(_population[i + 1][j]);
            newGen2.Add(_population[i][j]);
          }
          else
          {
            newGen.Add(_population[i][j]);
            newGen2.Add(_population[i + 1][j]);
          }
        }
        _populationAfterCrossingover.Add(newGen);
        _populationAfterCrossingover.Add(newGen2);
      }
      Console.WriteLine();
    }

    private static void CrossingoverUporyadochenniyOdnotochechniy()
    {
      //����� ������������� ����� ����� ���������� ��������. ����� ���������� ����������� ������ �������� �1 � �'1. 
      //��������� ������� � �'1 ������� �� �2 � ������������� ���� ����� �������, 
      //�������� ��������, ��� �������� � �'1. 
      //��������� �'2 ����� ����������� ���������� ���������. �������� ���������������� ����� ����������� ������ �������� �� �2, 
      //� ����� ������ �1 �������, ��������� ����. .
      _populationAfterCrossingover = new List<List<int>>();
      _tochkiRazriva = new List<List<int>>();
      var rnd = new Random();
      for (int i = 0; i < PERSON_COUNT; i += 2)
      {
        var tochkiRazrivaSub = new List<int>();
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT + 1));
        _tochkiRazriva.Add(tochkiRazrivaSub);
        var newGen = new List<int>();
        var newGen2 = new List<int>();
        for (int j = 0; j < GEN_COUNT; j++)
        {
          if (j >= tochkiRazrivaSub[0])
          {
            for (int x = 0; x < GEN_COUNT; x++)
              //����� �������� �� (��������� 2) �������� ��� ���� � ��������� ����, ��� ���������� � (����� ��������� 1)
            {
              if (!newGen.Exists(g = > g == _population[i + 1][x]))
              {
                newGen.Add(_population[i + 1][x]);
                break;
              }
            }
            for (int x = 0; x < GEN_COUNT; x++)
              //����� �������� �� (��������� 1) �������� ��� ���� � ��������� ����, ��� ���������� � (����� ��������� 2)
            {
              if (!newGen2.Exists(g = > g == _population[i][x]))
              {
                newGen2.Add(_population[i][x]);
                break;
              }
            }
          }
          else
          {
            newGen.Add(_population[i][j]);
            newGen2.Add(_population[i + 1][j]);
          }
        }
        _populationAfterCrossingover.Add(newGen);
        _populationAfterCrossingover.Add(newGen2);
      }
      Console.WriteLine();
    }

    private static void CrossingoverChastichSootvetOdnotochechniy()
    {
      //����� ����� �������� ���������� ������������� ����� ��� ����� ��. 
      //������ ������������� �������� (�����) � ����� ���������� � ��������������� 
      //��������� ������������ ����� ���������� ������� � ������� ��������� � ������������� ��������. 
      //��� ���� ������ ������� P2 ����������� � P'1, ����� ������� �1 ����������� � P'1 
      //� ������� ������������� ����� �� ������������� ����, ����������� � ��������� ������������. 

      _populationAfterCrossingover = new List<List<int>>();
      _tochkiRazriva = new List<List<int>>();
      var rnd = new Random();
      for (int i = 0; i < PERSON_COUNT; i += 2)
      {
        var tochkiRazrivaSub = new List<int>();
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT + 1));
        _tochkiRazriva.Add(tochkiRazrivaSub);
        var newGen = new List<int>();
        var newGen2 = new List<int>();
        for (int j = 0; j < GEN_COUNT; j++)
        {
          if (j < tochkiRazrivaSub[0])
          {
            newGen.Add(-1);
            newGen2.Add(-1);
          }
          else
          {
            newGen.Add(_population[i + 1][j]);
            newGen2.Add(_population[i][j]);
          }
        }
        for (int j = 0; j < tochkiRazrivaSub[0]; j++) //��� ������, ���� ������ ����� ���������
        {
          var index = j;
          while (true)
          {
            if (!newGen.Exists(g = > g == _population[i][index]))
            {
              newGen[j] = _population[i][index];
              break;
            }
            index = newGen.IndexOf(_population[i][index]);
          }
        }
        for (int j = 0; j < tochkiRazrivaSub[0]; j++)
        {
          var index = j;
          while (true)
          {
            if (!newGen2.Exists(g = > g == _population[i + 1][index]))
            {
              newGen2[j] = _population[i + 1][index];
              break;
            }
            index = newGen2.IndexOf(_population[i + 1][index]);
          }
        }
        _populationAfterCrossingover.Add(newGen);
        _populationAfterCrossingover.Add(newGen2);
      }
    }

    private static void CrossingoverCiklicheskiy()
    {
      //����� ������� ������ ������������� ��������� ������������� ������������ ��� ���������� ����� ��, 
      //��� ����������� ����� ��, ������� ������ ������������ ��������.
      //��� ����� ���������� ����� � ���� ����������, ��� ��� ������ ���� �����������.

      _populationAfterCrossingover = new List<List<int>>();
      _tochkiRazriva = new List<List<int>>();
      var rnd = new Random();
      for (var i = 0; i < PERSON_COUNT; i += 2)
      {
        var tochkiRazrivaSub = new List<int>();
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT + 1));
        _tochkiRazriva.Add(tochkiRazrivaSub);
        var newGen = new List<int>();
        var newGen2 = new List<int>();
        for (int j = 0; j < GEN_COUNT; j++)
        {
          newGen.Add(-1);
          newGen2.Add(-1);
        }
        for (var j = 0; j < GEN_COUNT; j++)
        {
          newGen[_population[i][j]] = _population[i + 1][j];
          newGen2[_population[i + 1][j]] = _population[i][j];
        }
        _populationAfterCrossingover.Add(newGen);
        _populationAfterCrossingover.Add(newGen2);
      }
    }

    private static void MutationOdnotochechniy()
    {
      //��� ��� ���������� �������� �������� ��� � ������������ ��������� �, 
      //��������� ��� �� ����� ������������� ���, �������� ��������� �������

      _populationAfterCrossingover = new List<List<int>>();
      _tochkiRazriva = new List<List<int>>();
      var rnd = new Random();
      for (var i = 0; i < PERSON_COUNT; i++)
      {
        var tochkiRazrivaSub = new List<int>();
        tochkiRazrivaSub.Add(rnd.Next(1, GEN_COUNT));
        _tochkiRazriva.Add(tochkiRazrivaSub);
        var newGen = new List<int>();
        for (var j = 0; j < GEN_COUNT; j++)
        {
          newGen.Add(_population[i][j]);
        }
        var stakan = newGen[tochkiRazrivaSub[0] - 1];
        newGen[tochkiRazrivaSub[0] - 1] = newGen[tochkiRazrivaSub[0]];
        newGen[tochkiRazrivaSub[0]] = stakan;

        _populationAfterCrossingover.Add(newGen);
      }
    }

    private static void MutationDvuhtochechniy()
    {
      //��� ���������� ������������� �� ��������� ��� ������������ ������� ���������� ��� ����� �������.
      //����� ������������ ������������ ����� ����� �����, ������������� ������ �� ����� �������. 

      _populationAfterCrossingover = new List<List<int>>();
      _tochkiRazriva = new List<List<int>>();
      var rnd = new Random();
      for (var i = 0; i < PERSON_COUNT; i++)
      {
        var tochkiRazrivaSub = new List<int>();
        tochkiRazrivaSub.Add(rnd.Next(1, GEN_COUNT - 1));
        tochkiRazrivaSub.Add(rnd.Next(1, GEN_COUNT - 1));
        _tochkiRazriva.Add(tochkiRazrivaSub);
        var newGen = new List<int>();
        for (var j = 0; j < GEN_COUNT; j++)
        {
          newGen.Add(_population[i][j]);
        }
        var stakan = newGen[tochkiRazrivaSub[1]];
        newGen[tochkiRazrivaSub[1]] = newGen[tochkiRazrivaSub[0]];
        newGen[tochkiRazrivaSub[0]] = stakan;

        _populationAfterCrossingover.Add(newGen);
      }
    }

    private static void MutationInversionOdnoTochechnaya()
    {
      //�������� �����������, ����������� �� ������ �������������� ������������ ��������� 
      //(��� �� �����) ��������� ��������� �������. ��� ��� ���������� ��������� ������� 
      //������������ ���� ��� ��������� ����� ������� (��������), ������ ������� �������� �������������.
      _populationAfterCrossingover = new List<List<int>>();
      _tochkiRazriva = new List<List<int>>();
      var rnd = new Random();
      for (var i = 0; i < PERSON_COUNT; i++)
      {
        var tochkiRazrivaSub = new List<int>();
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT - 1));
        _tochkiRazriva.Add(tochkiRazrivaSub);
        var newGen = new List<int>();

        for (var j = 0; j < GEN_COUNT; j++)
        {
          if (j < tochkiRazrivaSub[0])
          {
            newGen.Add(_population[i][j]);
          }
          else
          {
            newGen.Add(_population[i][GEN_COUNT - j + tochkiRazrivaSub[0] - 1]);
          }
        }
        _populationAfterCrossingover.Add(newGen);
      }
    }

    private static void MutationInversionDvuhTochechnaya()
    {
      //�������� �����������, ����������� �� ������ �������������� ������������ ��������� 
      //(��� �� �����) ��������� ��������� �������. ��� ��� ���������� ��������� ������� 
      //������������ ���� ��� ��������� ����� ������� (��������), ������ ������� �������� �������������.
      _populationAfterCrossingover = new List<List<int>>();
      _tochkiRazriva = new List<List<int>>();
      var rnd = new Random();
      for (var i = 0; i < PERSON_COUNT; i++)
      {
        var tochkiRazrivaSub = new List<int>();
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT - 1));
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT - 1));
        tochkiRazrivaSub.Sort();
        _tochkiRazriva.Add(tochkiRazrivaSub);
        var newGen = new List<int>();

        for (var j = 0; j < GEN_COUNT; j++)
        {
          if (j < tochkiRazrivaSub[0] || j > tochkiRazrivaSub[1])
          {
            newGen.Add(_population[i][j]);
          }
          else
          {
            newGen.Add(_population[i][tochkiRazrivaSub[1] - j + tochkiRazrivaSub[0]]);
          }
        }
        _populationAfterCrossingover.Add(newGen);
      }
    }

    private static void CrossingoverMutationTranslakation()
    {
      //�������� �����������, ����������� �� ������ ����������� � �������������� �� ���� 
      //������������ �������� (��� �� ������) ��������� ��� ��������� ��������. 
      //������� �������, �� ������������ ����� ���������� ���������� ������������� � ��������.
      //� �������� ��� ���������� ��������� ������� ������������ ���� ������ � ������ ���������.
      //��� ������������ ������� В1 ������� ����� ����� �� ������� �� �������� �1 � �������� ������ 
      //����� �� ������� �� �2 .��� �������� В2 ������� ����� ����� �2 � �������� ������ ����� �1. 

      _populationAfterCrossingover = new List<List<int>>();
      _tochkiRazriva = new List<List<int>>();
      var rnd = new Random();
      for (var i = 0; i < PERSON_COUNT; i += 2)
      {
        var tochkiRazrivaSub = new List<int>();
        tochkiRazrivaSub.Add(rnd.Next(0, GEN_COUNT - 1));
        tochkiRazrivaSub.Sort();
        _tochkiRazriva.Add(tochkiRazrivaSub);
        var newGen = new List<int>();
        var newGen2 = new List<int>();

        for (var j = 0; j < GEN_COUNT; j++)
        {
          if (j < tochkiRazrivaSub[0])
          {
            newGen.Add(_population[i][j]);
            newGen2.Add(_population[i + 1][j]);
          }
          else
          {
            newGen.Add(_population[i + 1][GEN_COUNT - j + tochkiRazrivaSub[0] - 1]);
            newGen2.Add(_population[i][GEN_COUNT - j + tochkiRazrivaSub[0] - 1]);
          }
        }
        _populationAfterCrossingover.Add(newGen);
        _populationAfterCrossingover.Add(newGen2);
      }
    }

    private static void MutationDeleciyaDvuhTochechnaya()
    {
      //�������� ����������� ������� ���������

      _populationAfterCrossingover = new List<List<int>>();
      _tochkiRazriva = new List<List<int>>();
      var rnd = new Random();
      for (var i = 0; i < PERSON_COUNT; i++)
      {
        var tochkiRazrivaSub = new List<int>();
        tochkiRazrivaSub.Add(rnd.Next(1, GEN_COUNT - 1));
        tochkiRazrivaSub.Add(rnd.Next(1, GEN_COUNT - 1));
        tochkiRazrivaSub.Sort();
        _tochkiRazriva.Add(tochkiRazrivaSub);
        var newGen = new List<int>();
        for (var j = 0; j < GEN_COUNT; j++)
        {
          if (j < tochkiRazrivaSub[0] || j >= tochkiRazrivaSub[1])
          {
            newGen.Add(_population[i][j]);
          }
        }
        for (var j = 0; j < GEN_COUNT; j++)
        {
          if (j >= tochkiRazrivaSub[0] && j < tochkiRazrivaSub[1])
          {
            newGen.Add(-1);
          }
        }
        _populationAfterCrossingover.Add(newGen);
      }
    }

    private static void PopulationsShow(string str)
    {
      Console.WriteLine(str);
      for (int i = 0; i < PERSON_COUNT; i++)
      {
        Console.Write(i + ": ");
        PopulationShow(_population[i]);
        Console.WriteLine();
      }
    }

    private static void PopulationsShowAfterAndBeforeCrossingover(string str, int razrivCount)
    {
      //��������� ��� ������ ���� ��������� �� � ����� �������� � ����� �������
      Console.WriteLine(str);
      for (int i = 0; i < PERSON_COUNT; i += 2)
      {
        Console.Write("��: \r\n" + i + ": ");
        PopulationShow(_population[i]);
        Console.WriteLine();
        Console.Write(i + 1 + ": ");
        PopulationShow(_population[i + 1]);
        Console.WriteLine();
        Console.Write("�����: ");
        if (razrivCount > 0)
        {
          Console.Write("����� �������=");
          for (int x = 0; x < razrivCount; x++)
          {
            Console.Write(" " + _tochkiRazriva[i / 2][x]);
          }
        }
        Console.Write("\r\n" + i + ": ");
        PopulationShow(_populationAfterCrossingover[i]);
        Console.WriteLine();
        Console.Write(i + 1 + ": ");
        PopulationShow(_populationAfterCrossingover[i + 1]);
        Console.WriteLine("\r\n______________________________");
      }
    }

    private static void PopulationsShowAfterAndBeforeMutation(string str, int mutationCount)
    {
      //��������� ��� ������ ���� ��������� �� � ����� �������� � ����� �������
      Console.WriteLine(str);
      for (int i = 0; i < PERSON_COUNT; i++)
      {
        Console.Write("��: \r\n" + i + ": ");
        PopulationShow(_population[i]);
        Console.WriteLine();
        Console.Write("�����: ");
        if (mutationCount > 0)
        {
          Console.Write("����� �������=");
          for (int x = 0; x < mutationCount; x++)
          {
            Console.Write(" " + _tochkiRazriva[i][x]);
          }
        }
        Console.Write("\r\n" + i + ": ");
        PopulationShow(_populationAfterCrossingover[i]);
        Console.WriteLine();
        Console.WriteLine("\r\n______________________________");
      }
    }

    private static void PopulationShow(List<int> population)
    {
      for (int j = 0; j < GEN_COUNT; j++)
      {
        Console.Write("{0,4} ", population[j]);
      }
    }
  }
}