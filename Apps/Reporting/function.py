import mysql.connector
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import requests
from pandas import DataFrame


def generateDf():
    r = requests.get('https://b4xcv1e397.execute-api.eu-west-3.amazonaws.com/dev/partie')
    x = pd.json_normalize(r.json())
    return x


def savePlotAsFile(fig, filename):
    fig.savefig(filename)


def plotByTimeWinning():
    df = generateDf()
    df = df.loc[(df['deathPosition']) == 100]
    elaspedDf = ((df["elapsedTime"].value_counts()).to_frame()).sort_index()
    labels = ["{0} - {1}".format(i, i + 19) for i in range(0, 200, 20)]
    c = pd.cut(elaspedDf.index, np.arange(0, 201, 20),
               include_lowest=True, right=False,
               labels=labels)
    ploter = elaspedDf.groupby(c).sum()
    # ploter.plot(kind='barh', figsize=(8, 8), xlabel="Temps sur la partie (s)", ylabel="Nombre de joueur mort",
    #             colormap="summer")
    ploter.plot(kind='bar', figsize=(6, 9), xlabel="Temps sur la partie (s)", ylabel="Nombre de joueur mort",
                colormap="summer", title="Nombre de joueur ayant fini le niveau par tranche de temps \n ")
    savePlotAsFile(plt.gcf(), "resources/plotTimeByWinning")
    plt.show()


def plotByDeathPosition():
    df = generateDf()
    df = df.loc[df["deathPosition"] != 100]
    deathPosDf = ((df["deathPosition"].value_counts()).to_frame()).sort_index()
    labels = ["{0} - {1}".format(i, i + 9) for i in range(0, 100, 10)]
    c = pd.cut(deathPosDf.index, np.arange(0, 101, 10),
               include_lowest=True, right=False,
               labels=labels)
    ploter = deathPosDf.groupby(c).sum()
    # ploter.plot(kind='barh', figsize=(8, 8), xlabel="Pourcentage d'avancement", ylabel="Nombre de joueur mort",
    #             colormap="RdGy")
    ploter.plot(kind='bar', figsize=(6, 8), xlabel="Pourcentage d'avancement", ylabel="Nombre de joueur mort",
                colormap="RdGy")
    savePlotAsFile(plt.gcf(), 'resources/plotDeathPosition')
    plt.show()


def plotPlayersByScore():
    df = generateDf()
    df = df.loc[df["deathPosition"] != 101]
    scoreDf = ((df["scoreTotal"].value_counts()).to_frame()).sort_index()
    labels = ["{0} - {1}".format(i, i + 199) for i in range(0, 2600, 200)]
    c = pd.cut(scoreDf.index, np.arange(0, 2601, 200),
               include_lowest=True, right=False,
               labels=labels)
    print(df["scoreTotal"])
    ploter = scoreDf.groupby(c).sum()
    ploter.plot(kind='bar', figsize=(7, 10.5), xlabel="Score total", ylabel="Nombre de joueur",
                colormap="terrain")
    savePlotAsFile(plt.gcf(), 'resources/plotPlayersByScore')
    plt.show()


def plotKillsByTimes():
    df = generateDf()
    df.groupby("elapsedTime").sum().plot(kind='line', y='nbKill', ylabel="Nombre d'ennemie tué", xlabel='Temps passé')
    savePlotAsFile(plt.gcf(), 'resources/plotKillsByTimes')
    plt.show()


def plotScoreByTimes():
    df = generateDf()
    # df.plot(kind='scatter', y='scoreTotal', x='elapsedTime')

    df.groupby("elapsedTime").sum().plot(kind='line', y='scoreTotal', ylabel="Score total", xlabel="Temps passé")
    savePlotAsFile(plt.gcf(), 'resources/plotScoreByTime')

    plt.show()


def endGamePourcentage():
    df = generateDf()
    pourcentageDf = (df["isDead"].value_counts()).to_frame()
    x = getRealValue(pourcentageDf.values)
    plt.pie(x, labels=['Niveau Fini', "Niveau non terminé"], autopct='%1.1f%%', shadow=True,
            startangle=90)
    plt.title("Pourcentage des joueurs qui ont fini le niveau")
    savePlotAsFile(plt.gcf(), "resources/plotEndPourcentage")
    plt.show()


def getRealValue(l: list):
    x = []
    for i in range(len(l)):
        x.append(l[i][0])
    return x
