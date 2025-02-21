import matplotlib.pyplot
import numpy as np
import matplotlib.pyplot as plt
import matplotlib

def plot_rf(rf_series_dict, num_bins):
    fig = plt.figure(figsize=(12, 20))
    cmap = plt.get_cmap('jet')
    for ii, key in enumerate(rf_series_dict.keys()):
        rf_series = rf_series_dict[key]
        ax = fig.add_subplot(1,len(rf_series_dict),ii + 1, projection='3d')

        froms = rf_series.index.get_level_values("from").mid
        tos = rf_series.index.get_level_values("to").mid

        width = rf_series.index.get_level_values('from').length.min()
        depth = rf_series.index.get_level_values('to').length.min()
        bottom = np.zeros_like(rf_series)

        max_height = np.max(rf_series)
        min_height = np.min(rf_series)
        rgba = [cmap((k-min_height)/max_height) for k in rf_series]
        ax.set_xlabel('From')
        ax.set_ylabel('To')
        ax.set_zlabel('Count')
        ax.bar3d(froms.ravel(), tos.ravel(), bottom, width, depth, rf_series,
                 color=rgba, shade=True, zsort='average')
        ax.set_title(key)

        # Set axis limits to control the size of the plane
        ax.set_xlim([0, num_bins])  # Set the range for the x-axis
        ax.set_ylim([0, num_bins])      # Set the range for the y-axis
        ax.set_zlim([0, max_height])

    return fig