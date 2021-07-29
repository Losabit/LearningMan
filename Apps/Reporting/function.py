import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import requests
from pandas import DataFrame

def clearPlot():
    plt.cla()   # Clear axis
    plt.clf()
    plt.close()

def generateDf():
    r = requests.get('https://b4xcv1e397.execute-api.eu-west-3.amazonaws.com/dev/partie')
    x = pd.json_normalize(r.json())
    return x


def savePlotAsFile(fig, filename):
    fig.savefig(filename,transparent=True)


def plotByTimeWinning():
    df = generateDf()
    df = df.loc[(df['deathPosition']) == 100]
    elaspedDf = ((df["elapsedTime"].value_counts()).to_frame()).sort_index()
    labels = ["{0} - {1}".format(i, i + 9) for i in range(0, 80, 10)]
    c = pd.cut(elaspedDf.index, np.arange(0, 81, 10),
               include_lowest=True, right=False,
               labels=labels)
    ploter = elaspedDf.groupby(c).sum()
    # ploter.plot(kind='barh', figsize=(8, 8), xlabel="Temps sur la partie (s)", ylabel="Nombre de joueur mort",
    #             colormap="summer")
    ploter.plot(kind='bar', figsize=(6, 9), xlabel="Time spent", ylabel="Nb AI",
                colormap="summer", title="Number of players who finished the level per time slice \n ")
    savePlotAsFile(plt.gcf(), "resources/plotTimeByWinning")
    plt.show()
    clearPlot()


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
    ploter.plot(kind='bar', figsize=(6, 8), xlabel="Percentage of completion", ylabel="Number of players", title='Death position of players',
                colormap="RdGy")
    savePlotAsFile(plt.gcf(), 'resources/plotDeathPosition')
    plt.show()
    clearPlot()


def plotPlayersByScore():
    df = generateDf()
    df = df.loc[df["deathPosition"] != 101]
    scoreDf = ((df["scoreTotal"].value_counts()).to_frame()).sort_index()
    labels = ["{0} - {1}".format(i, i + 199) for i in range(0, 3000, 200)]
    c = pd.cut(scoreDf.index, np.arange(0, 3001, 200),
               include_lowest=True, right=False,
               labels=labels)
    print(df["scoreTotal"])
    ploter = scoreDf.groupby(c).sum()
    print(ploter)
    ploter.plot(kind='bar', figsize=(7, 10.5), xlabel="Total score", ylabel="Number of player", title="Players by score",colormap="terrain")
    savePlotAsFile(plt.gcf(), 'resources/plotPlayersByScore')
    plt.show()
    clearPlot()


def plotKillsByTimes():
    df = generateDf()
    df.groupby("elapsedTime").sum().plot(kind='line', y='nbKill', ylabel="Number of ennemies killed", xlabel='Time spent', title='Kill by time for players')
    savePlotAsFile(plt.gcf(), 'resources/plotKillsByTimes')
    plt.show()
    clearPlot()


def plotScoreByTimes():
    df = generateDf()
    # df.plot(kind='scatter', y='scoreTotal', x='elapsedTime')

    df.groupby("elapsedTime").sum().plot(kind='line', y='scoreTotal', ylabel="Total score", xlabel="TIme spent", title='Score By Times')
    savePlotAsFile(plt.gcf(), 'resources/plotScoreByTime')

    plt.show()
    clearPlot()


def endGamePourcentage():
    df = generateDf()
    pourcentageDf = (df["isDead"].value_counts()).to_frame()
    x = getRealValue(pourcentageDf.values)
    labels = ['Level not completed', "Level completed"]
    pourcentageDf = (df["isDead"].value_counts()).to_frame()
    if len(pourcentageDf) < 2:
        index = pourcentageDf.index
        print(index[0])
        if index[0] == 1:
            labels = ['Level Not Completed']
        else:
            labels = ['Level Completed']
    else:
        labels = ['Level not completed', "Level completed"]

    x = getRealValue(pourcentageDf.values)
    plt.pie(x, labels=labels, autopct='%1.1f%%', shadow=True,
            startangle=90)
    plt.title("Level distribution completed")
    savePlotAsFile(plt.gcf(), "resources/plotEndPourcentageAI")
    plt.show()
    clearPlot()


def plotByTimeWinningAI():
    df = generateDf()
    df = df.loc[((df['deathPosition']) == 100) & ((df['playerType']) == 1)]
    elaspedDf = ((df["elapsedTime"].value_counts()).to_frame()).sort_index()
    labels = ["{0} - {1}".format(i, i + 9) for i in range(0, 80, 10)]
    c = pd.cut(elaspedDf.index, np.arange(0, 81, 10),
               include_lowest=True, right=False,
               labels=labels)
    ploter = elaspedDf.groupby(c).sum()
    # ploter.plot(kind='barh', figsize=(8, 8), xlabel="Temps sur la partie (s)", ylabel="Nombre de joueur mort",
    #             colormap="summer")
    ploter.plot(kind='bar', figsize=(6, 9), xlabel="Time spent (s)", ylabel="Nb AI",
                colormap="summer", title="Number of IA who finished the level per time slice \n ")
    savePlotAsFile(plt.gcf(), "resources/plotTimeByWinningAI")
    plt.show()
    clearPlot()


def plotByDeathPositionAI():
    df = generateDf()
    df = df.loc[(df["deathPosition"] != 100) & ((df['playerType']) == 1)]
    deathPosDf = ((df["deathPosition"].value_counts()).to_frame()).sort_index()
    labels = ["{0} - {1}".format(i, i + 9) for i in range(0, 100, 10)]
    c = pd.cut(deathPosDf.index, np.arange(0, 101, 10),
               include_lowest=True, right=False,
               labels=labels)
    ploter = deathPosDf.groupby(c).sum()
    # ploter.plot(kind='barh', figsize=(8, 8), xlabel="Pourcentage d'avancement", ylabel="Nombre de joueur mort",
    #             colormap="RdGy")
    ploter.plot(kind='bar', figsize=(6, 8), xlabel="percentage of completion", ylabel="Number of dead AI",
                colormap="RdGy",title='IA death localisation')
    savePlotAsFile(plt.gcf(), 'resources/plotDeathPositionAI')
    plt.show()
    clearPlot()


def plotPlayersByScoreAI():
    df = generateDf()
    df = df.loc[(df["deathPosition"] != 101) & ((df['playerType']) == 1)]
    scoreDf = ((df["scoreTotal"].value_counts()).to_frame()).sort_index()
    labels = ["{0} - {1}".format(i, i + 199) for i in range(0, 3000, 200)]
    c = pd.cut(scoreDf.index, np.arange(0, 3001, 200),
               include_lowest=True, right=False,
               labels=labels)
    print(df["scoreTotal"])
    ploter = scoreDf.groupby(c).sum()
    print(ploter)
    ploter.plot(kind='bar', figsize=(7, 10.5), xlabel="Total score", ylabel="Nb IA",
                colormap="terrain", title = "Number of IA by score")
    savePlotAsFile(plt.gcf(), 'resources/plotPlayersByScoreAI')
    plt.show()
    clearPlot()


def plotKillsByTimesAI():
    df = generateDf()
    df = df.loc[((df['playerType']) == 1)]
    df.groupby("elapsedTime").sum().plot(kind='line', y='nbKill', ylabel="Number of Ennemies Killed", xlabel='TIme spent',title = "Kill by time for AI")
    savePlotAsFile(plt.gcf(), 'resources/plotKillsByTimesAI')
    plt.show()
    clearPlot()


def plotScoreByTimesAI():
    df = generateDf()
    df = df.loc[((df['playerType']) == 1)]

    # df.plot(kind='scatter', y='scoreTotal', x='elapsedTime')

    df.groupby("elapsedTime").sum().plot(kind='line', y='scoreTotal', ylabel=" Total score ", xlabel="TIme spent", title="Score by Time for AI")
    savePlotAsFile(plt.gcf(), 'resources/plotScoreByTimeAI')

    plt.show()
    clearPlot()


def endGamePourcentageIA():
    df = generateDf()
    df = df.loc[((df['playerType']) == 1)]
    labels = ['Level not completed', "Level completed"]
    pourcentageDf = (df["isDead"].value_counts()).to_frame()
    if len(pourcentageDf) < 2:
        index = pourcentageDf.index
        print(index[0])
        if index[0] == 1:
            labels = ['Level Not Completed']
        else:
            labels = ['Level Completed']
    else:
        labels = ['Level not completed', "Level completed"]

    x = getRealValue(pourcentageDf.values)
    plt.pie(x, labels=labels, autopct='%1.1f%%', shadow=True,
            startangle=90)
    plt.title("Level distribution completed")
    savePlotAsFile(plt.gcf(), "resources/plotEndPourcentageAI")
    plt.show()
    clearPlot()

def getRealValue(l: list):
    x = []
    for i in range(len(l)):
        x.append(l[i][0])
    return x
