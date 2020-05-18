//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include "file_handler.h"
#include "status.h"
#include "best_scores.h"

const char FileHandler::kScoresUrl[] = "resources/scores.dat";

Status FileHandler::LoadBestScores(BestScores* scores) const {
  FILE* scores_file = fopen(kScoresUrl, "r");
  if (scores_file == NULL)
    return kError;

  // To set an upper limit on the number of loaded scores,
  // we prevent stack overflow.
  for (int i = 0; !feof(scores_file); ++i) {
    int score;
    fscanf(scores_file, "%d ", &score);
    scores->AddBestScore(score);
  }

  fclose(scores_file);
  return kSuccess;
}

void FileHandler::SaveBestScores(const BestScores& scores) const {
  FILE* scores_file = fopen(kScoresUrl, "w");
  for (int i = 0; i < scores.num_best_scores(); ++i)
    fprintf(scores_file, "%d ", scores.best_score(i + 1));
  fclose(scores_file);
}